// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SocietySimulatorHUD.generated.h"

/**
 * 
 */
UCLASS()
class SOCIETYSIMULATOR_API ASocietySimulatorHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;
	FVector2D InitialPoint;
	FVector2D CurrentPoint;
	FVector2D GetMousePos2D();
	bool bStartSelecting = false;
	TArray <APawn*> FoundPawns;
};
