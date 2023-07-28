// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SocietySimulatorBuilding.h"
#include "SocietySimulatorCharacter.h"
#include "SocietySimulatorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USocietySimulatorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SOCIETYSIMULATOR_API ISocietySimulatorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddUnitToBox(UUserWidget* input);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ClearSelectedUnits();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SelectSingleUnit(AActor* Unit);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ProduceUnit(ASocietySimulatorBuilding* Building, TSubclassOf<ASocietySimulatorCharacter> Unit);
};
