// Fill out your copyright notice in the Description page of Project Settings.


#include "ProduceUnitWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


//UProduceUnitWidget::UProduceUnitWidget() {
//	static ConstructorHelpers::FClassFinder<ASocietySimulatorCharacter> UnitFound(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Character/BP_Character1.BP_Character1_C'"));
//	if (UnitFound.Class != nullptr) {
//		UnitC = UnitFound.Class;
//	}
//}

void UProduceUnitWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ProduceButton->OnClicked.AddDynamic(this, &UProduceUnitWidget::OnClick);
	
}

void UProduceUnitWidget::OnClick()
{
	//UE_LOG(LogTemp, Warning, TEXT("Click"));
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("33"));
	//static ConstructorHelpers::FClassFinder<ASocietySimulatorCharacter> UnitFound(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Character/BP_Character1.BP_Character1_C'"));
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("33"));
	//UE_LOG(LogTemp, Warning, TEXT("Click"));
	/*TSubclassOf<ASocietySimulatorCharacter> UnitC;
	if (UnitFound.Class != nullptr) {
		UnitC = UnitFound.Class;
	}*/
	UnitC = LoadClass<ASocietySimulatorCharacter>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Character/BP_Character1.BP_Character1_C'"));
	ISocietySimulatorInterface* TheInterface = Cast<ISocietySimulatorInterface>(UGameplayStatics::GetPlayerController(this, 0));
	if (TheInterface) {
		TheInterface->Execute_ProduceUnit(UGameplayStatics::GetPlayerController(this, 0), BuildingReference, UnitC);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("executed"));
	}
}
