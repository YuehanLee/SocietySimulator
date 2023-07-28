// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SocietySimulatorBuilding.h"
#include "SocietySimulatorInterface.h"
#include "SocietySimulatorCharacter.h"
#include "ProduceUnitWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOCIETYSIMULATOR_API UProduceUnitWidget : public UUserWidget, public ISocietySimulatorInterface
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ProduceButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* UnitImage;
	UFUNCTION()
	void OnClick();
	ASocietySimulatorBuilding* BuildingReference;
	TSubclassOf<ASocietySimulatorCharacter> UnitC;
};
