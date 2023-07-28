// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectedBuildingWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "Components/SlateWrapperTypes.h"
#include "SocietySimulatorBuilding.h"
#include "Misc/Attribute.h"

bool USelectedBuildingWidget::Initialize()
{
	Super::Initialize();

	UnitProductionImage->VisibilityDelegate.BindUFunction(this, "CheckFirstProduce");
	UnitProductionBar->VisibilityDelegate.BindUFunction(this, "CheckFirstProduce");
	TextAddSign->VisibilityDelegate.BindUFunction(this, "CheckFirstProduce");
	UnitProductionImage_1->VisibilityDelegate.BindUFunction(this, "CheckFirstProduce");
	UnitProductionImage_2->VisibilityDelegate.BindUFunction(this, "CheckFirstProduce");
	UnitProductionImage_3->VisibilityDelegate.BindUFunction(this, "CheckFirstProduce");
	
	return true;
}

ESlateVisibility USelectedBuildingWidget::CheckFirstProduce()
{
	ASocietySimulatorBuilding* input = Cast<ASocietySimulatorBuilding>(BuildingReference);
	if (input->IsProducingUnit) {
		
		return ESlateVisibility::Visible;
	}
	else
	{
		return ESlateVisibility::Hidden;
	}
	
}
