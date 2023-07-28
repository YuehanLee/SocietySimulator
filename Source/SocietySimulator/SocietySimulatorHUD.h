// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SocietySimulatorCharacter.h"
#include "SocietySimulatorBuilding.h"
#include "SocietySimulatorInterface.h"
#include "SocietySimulatorHUD.generated.h"

/**
 * 
 */
UCLASS()
class SOCIETYSIMULATOR_API ASocietySimulatorHUD : public AHUD, public ISocietySimulatorInterface
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;
	FVector2D InitialPoint;
	FVector2D CurrentPoint;
	FVector2D GetMousePos2D();
	bool bStartSelecting = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray <ASocietySimulatorCharacter*> FoundCharacters;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray <ASocietySimulatorBuilding*> FoundBuildings;
	void ClearSelectedUnits_Implementation() override;
	void SelectSingleUnit_Implementation(AActor* Unit) override;
};
