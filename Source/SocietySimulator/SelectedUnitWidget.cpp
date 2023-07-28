// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectedUnitWidget.h"
#include "Input/Events.h"
#include "Kismet/GameplayStatics.h"
#include "SocietySimulatorInterface.h"
#include "GameFramework/HUD.h"
#include "InputCoreTypes.h"

FReply USelectedUnitWidget::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);
	AHUD* MyHUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD();
	//UObject* MyObj = Cast<UObject>(MyHUD);
	ISocietySimulatorInterface* TheInterface = Cast<ISocietySimulatorInterface>(MyHUD);
	if (MouseEvent.FPointerEvent::IsMouseButtonDown(EKeys::LeftMouseButton)) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("pressed left mouse button"));
		if (TheInterface) {
			TheInterface->Execute_ClearSelectedUnits(MyHUD);
			TheInterface->Execute_SelectSingleUnit(MyHUD, UnitReference);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("deselect and single select"));
		}
		return FReply::Handled();
	}
	else {
		return FReply::Unhandled();
	}
}