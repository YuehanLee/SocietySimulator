// Fill out your copyright notice in the Description page of Project Settings.

#include "SocietySimulator.h"
#include "SocietySimulatorHUD.h"

void ASocietySimulatorHUD::DrawHUD()
{
	if (bStartSelecting == true) {
		CurrentPoint = GetMousePos2D();
		DrawRect(FLinearColor(0, 0, 1, .15f), InitialPoint.X, InitialPoint.Y, CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);
	}

}

FVector2D ASocietySimulatorHUD::GetMousePos2D()
{
	float PosX = 0;
	float PosY = 0;
	GetOwningPlayerController()->GetMousePosition(PosX, PosY);
	return FVector2D(PosX, PosY);
}