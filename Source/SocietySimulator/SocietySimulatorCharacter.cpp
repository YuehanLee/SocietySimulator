// Fill out your copyright notice in the Description page of Project Settings.


#include "SocietySimulatorCharacter.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "SelectedUnitWidget.h"
#include "Components/Image.h"
#include "SocietySimulatorPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


// Sets default values
ASocietySimulatorCharacter::ASocietySimulatorCharacter()
{

	SelectionDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	SelectionDecal->SetupAttachment(RootComponent);
	SelectionDecal->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	SelectionDecal->SetVisibility(false);
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<UUserWidget> SelectedUnitWidgetFound(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/BP_SelectedUnitWidget.BP_SelectedUnitWidget_C'"));
	if (SelectedUnitWidgetFound.Class != nullptr) {
		SelectedUnitWidgetC = SelectedUnitWidgetFound.Class;
	}

}

void ASocietySimulatorCharacter::IsWorking(ASocietySimulatorResource* input) {
	isWorking = true;
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Resource is working on character"));
	SelectedResource = input;
	TArray<AActor*> FoundBuildings;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASocietySimulatorBuilding::StaticClass(), FoundBuildings);
	if (FoundBuildings.Num() != 0) {
		for (int32 i = 0; i < FoundBuildings.Num(); i++) {
			//GEngine->AddOnScreenDebugMessage(-1, 1 / 60.0f, FColor::Yellow, FString::Printf(TEXT("%d"), i), false);
			ASocietySimulatorBuilding* FB = Cast<ASocietySimulatorBuilding>(FoundBuildings[i]);
			if (FB) {
				if (FB->GetDistanceTo(this) < ShortestDistance) {
					CollectResourceBuilding = FB;
					ShortestDistance = FB->GetDistanceTo(this);
				}
			}
		}
	}
	if (haveResource) {
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("character have resource"));
		FVector MoveLocation = CollectResourceBuilding->GetActorLocation();
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this->GetController(), MoveLocation);
		//haveResource = false;
	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("character dont have resource"));
		FVector MoveLocation = SelectedResource->GetActorLocation();
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this->GetController(), MoveLocation);
		//haveResource = true;

	}

}

void ASocietySimulatorCharacter::ContinueWorking()
{
	if (haveResource) {
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("character have resource"));
		FVector MoveLocation = CollectResourceBuilding->GetActorLocation();
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this->GetController(), MoveLocation);
		//haveResource = false;
	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("character dont have resource"));
		FVector MoveLocation = SelectedResource->GetActorLocation();
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this->GetController(), MoveLocation);
		//haveResource = true;

	}
}

void ASocietySimulatorCharacter::SetSelected()
{
	SelectionDecal->SetVisibility(true);
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("Selected"));
	//Cast<ASocietySimulatorPlayerController>(this->GetController())->AddUnitToBox(SelectedUnitWidget);
	//ISocietySimulatorInterface::AddUnitToBox(SelectedUnitWidget);
	ISocietySimulatorInterface* TheInterface = Cast<ISocietySimulatorInterface>(UGameplayStatics::GetPlayerController(this, 0));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("executed"));
	if (TheInterface) {
		TheInterface->Execute_AddUnitToBox(UGameplayStatics::GetPlayerController(this, 0),SelectedUnitWidget);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("executed"));
	}
}

void ASocietySimulatorCharacter::SetDeselected()
{
	SelectionDecal->SetVisibility(false);
	SelectedUnitWidget->RemoveFromParent();
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("Deselcted"));
}

// Called when the game starts or when spawned
void ASocietySimulatorCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*static ConstructorHelpers::FClassFinder<UUserWidget> SelectedUnitWidgetFound(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/SelectedUnitWidget.SelectedUnitWidget_C'"));
	if (SelectedUnitWidgetFound.Class != nullptr) {
		SelectedUnitWidget = SelectedUnitWidgetFound.Class;
	}
	UUserWidget* SelectedUnit = CreateWidget<UUserWidget>(this, SelectedUnitWidget);*/
	//TSubclassOf<UUserWidget> WidgetClass;
	SelectedUnitWidget = Cast<USelectedUnitWidget>(CreateWidget(GetWorld(), SelectedUnitWidgetC));
	//USelectedUnitWidget* SelectedUnitWidget;
	//SelectedUnitWidget = CreateWidget<USelectedUnitWidget>(GetWorld(), USelectedUnitWidget::StaticClass());
	SelectedUnitWidget->UnitReference = this;
	SelectedUnitWidget->UnitImage->SetBrushFromTexture(UnitIcon);

	//SelectedUnitWidget->AddToViewport(9999);
	//SelectedUnitWidget->AddToViewport();
	
}

// Called every frame
void ASocietySimulatorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void ASocietySimulatorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

