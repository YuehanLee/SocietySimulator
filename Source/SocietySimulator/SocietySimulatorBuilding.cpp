// Fill out your copyright notice in the Description page of Project Settings.


#include "SocietySimulatorBuilding.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Internationalization/Text.h"
#include "Components/BoxComponent.h"
#include "SocietySimulatorCharacter.h"
#include "ProduceUnitWidget.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASocietySimulatorBuilding::ASocietySimulatorBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	SelectionDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	SelectionDecal->SetupAttachment(RootComponent);
	SelectionDecal->SetVisibility(false);
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(RootComponent);
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);
	static ConstructorHelpers::FClassFinder<UUserWidget> SelectedBuildingWidgetFound(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/BP_SelectedBuildingWidget.BP_SelectedBuildingWidget_C'"));
	if (SelectedBuildingWidgetFound.Class != nullptr) {
		SelectedBuildingWidgetC = SelectedBuildingWidgetFound.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> ActionBoxButtonFound(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/BP_ProduceUnitWidget.BP_ProduceUnitWidget_C'"));
	if (ActionBoxButtonFound.Class != nullptr) {
		ActionBoxButton1C = ActionBoxButtonFound.Class;
	}
}

void ASocietySimulatorBuilding::SetSelected()
{
	SelectionDecal->SetVisibility(true);
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("Selected"));
	SelectedBuildingWidget->AddToViewport();
}

void ASocietySimulatorBuilding::SetDeselected()
{
	SelectionDecal->SetVisibility(false);
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("Deselcted"));
	SelectedBuildingWidget->RemoveFromParent();
}

void ASocietySimulatorBuilding::AddUnitToQueue(TSubclassOf<AActor> Unit)
{
	UnitProductionQueue.Add(Unit);
}

// Called when the game starts or when spawned
void ASocietySimulatorBuilding::BeginPlay()
{
	Super::BeginPlay();
	UProduceUnitWidget* ProduceUnitWidget = Cast<UProduceUnitWidget>(CreateWidget(GetWorld(), ActionBoxButton1C));
	ProduceUnitWidget->BuildingReference = this;
	if (ProduceUnitWidget == nullptr) {
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("null"));
	}
	ActionBoxButton.Add(ProduceUnitWidget);
	for (int32 i = 0; i < ActionBoxButton.Num(); i++) {
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("suc1"));
	}
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASocietySimulatorBuilding::BeginOverlap);
	SelectedBuildingWidget = Cast<USelectedBuildingWidget>(CreateWidget(GetWorld(), SelectedBuildingWidgetC));
	//if (SelectedBuildingWidget) { 
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("suc"));
	//}
	for (int32 i = 0; i < ActionBoxButton.Num(); i++) {
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("suc"));
		SelectedBuildingWidget->ActionBox->AddChildToWrapBox(ActionBoxButton[i]);
	}
	SelectedBuildingWidget->BuildingReference = this;
	SelectedBuildingWidget->BuildingImage->SetBrushFromTexture(BuildingIcon);
	SelectedBuildingWidget->BuildingNameText->SetText(FText::FromString(BuildingName));

	

}

void ASocietySimulatorBuilding::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("building overlap"));
	ASocietySimulatorCharacter* CollideCharacter = Cast<ASocietySimulatorCharacter>(OtherActor);
	if (CollideCharacter) {
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("building overlap"));
		CollideCharacter->StoreResource();
		CollideCharacter->ContinueWorking();
	}
}

// Called every frame
void ASocietySimulatorBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("11"));
	if (!IsProducingUnit) {
		if (UnitProductionQueue.Num() > 0) {
			UnitBeingProduced = UnitProductionQueue[0];
			ASocietySimulatorCharacter* Default = Cast<ASocietySimulatorCharacter>(UnitProductionQueue[0]);
			if (Default != nullptr) {
				CurrentProductionTime = Default->ProductionTime;
				UnitProductionQueue.RemoveAt(0);
				IsProducingUnit = true;
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 1.0f/60, FColor::Black, TEXT("error"));
			}
			
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("11"));
		}
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("33"));
	}
	else {
		ProductionTimeSpend = ProductionTimeSpend + DeltaTime;
		ProductionProgress = ProductionTimeSpend / CurrentProductionTime;
		if (ProductionProgress >= 1) {
			FActorSpawnParameters SpawnParams;
			//TSubclassOf<ASocietySimulatorCharacter> ActorToSpawn;
			GetWorld()->SpawnActor<ASocietySimulatorCharacter>(UnitBeingProduced,Collision->GetComponentLocation(), Collision->GetComponentRotation(), SpawnParams);
			ProductionTimeSpend = 0;
			ProductionProgress = 0;
			UnitBeingProduced = NULL;
			IsProducingUnit = false;
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("22"));
		}
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("44"));
	}

}

