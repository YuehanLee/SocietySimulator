// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectedUnitWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOCIETYSIMULATOR_API USelectedUnitWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	AActor* UnitReference;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* UnitImage;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) ;
	
};
