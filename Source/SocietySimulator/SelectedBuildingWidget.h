// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectedBuildingWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOCIETYSIMULATOR_API USelectedBuildingWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	bool Initialize() override;

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* BuildingImage;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* BuildingNameText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* UnitProductionBar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* UnitProductionImage;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextAddSign;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* UnitProductionImage_1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* UnitProductionImage_2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* UnitProductionImage_3;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWrapBox* ActionBox;
	UFUNCTION()
	ESlateVisibility CheckFirstProduce();

	AActor* BuildingReference;
	
};
