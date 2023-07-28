// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectedUnitsArea.generated.h"

/**
 * 
 */
UCLASS()
class SOCIETYSIMULATOR_API USelectedUnitsArea : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* UnitsBox;

};
