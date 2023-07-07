// Fill out your copyright notice in the Description page of Project Settings.

#include "SocietySimulator.h"
#include "SocietySimulatorHUD.h"

void ASocietySimulatorHUD::DrawHUD()
{
	if (bStartSelecting == true) {
		CurrentPoint = GetMousePos2D();
		DrawRect(FLinearColor(0, 0, 1, .15f), InitialPoint.X, InitialPoint.Y, CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);
	}
	TSubclassOf<APawn> CubePawn = LoadClass<APawn>(nullptr, TEXT("/Game/BP_PawnCube"));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ddd"));
	FoundPawns.Empty();
	GetActorsInSelectionRectangle<APawn>(InitialPoint, CurrentPoint, FoundPawns, false, false);
	if (FoundPawns.Num() != 0) {
		for (int32 i = 0; i < FoundPawns.Num(); i++) {
			GEngine->AddOnScreenDebugMessage(-1, 1/60.0f, FColor::Yellow, FString::Printf(TEXT("%d"), i), false);
		}
	}
	
	//int32 x = FoundPawns.Num();
	//FString x = FString::FromInt(x);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"), x), false);

}

FVector2D ASocietySimulatorHUD::GetMousePos2D()
{
	float PosX = 0;
	float PosY = 0;
	GetOwningPlayerController()->GetMousePosition(PosX, PosY);
	return FVector2D(PosX, PosY);
}