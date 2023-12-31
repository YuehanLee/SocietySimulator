// Fill out your copyright notice in the Description page of Project Settings.

#include "SocietySimulator.h"
#include "SocietySimulatorPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SocietySimulatorHUD.h"

void ASocietySimulatorHUD::DrawHUD()
{
	if (bStartSelecting == true) {
		CurrentPoint = GetMousePos2D();
		DrawRect(FLinearColor(0, 0, 1, .15f), InitialPoint.X, InitialPoint.Y, CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);
		if (FoundCharacters.Num() > 0)
		{
			for (int32 i = 0; i < FoundCharacters.Num(); i++)
			{
				FoundCharacters[i]->SetDeselected();
			}
		}
		/*if (FoundBuildings.Num() > 0)
		{
			for (int32 i = 0; i < FoundBuildings.Num(); i++)
			{
				FoundBuildings[i]->SetDeselected();
			}
		}*/
		FoundCharacters.Empty();
		FoundBuildings.Empty();
		GetActorsInSelectionRectangle<ASocietySimulatorCharacter>(InitialPoint, CurrentPoint, FoundCharacters, false, false);
		//GetActorsInSelectionRectangle<ASocietySimulatorBuilding>(InitialPoint, CurrentPoint, FoundBuildings, false, false);
		if (FoundCharacters.Num() != 0) {
			for (int32 i = 0; i < FoundCharacters.Num(); i++) {
				//GEngine->AddOnScreenDebugMessage(-1, 1/60.0f, FColor::Yellow, FString::Printf(TEXT("%d"), i), false);
			}
		}
		/*if (FoundBuildings.Num() != 0) {
			for (int32 i = 0; i < FoundBuildings.Num(); i++) {
				GEngine->AddOnScreenDebugMessage(-1, 1 / 60.0f, FColor::Green, FString::Printf(TEXT("%d"), i), false);
			}
		}*/
		if (FoundCharacters.Num() > 0)
		{
			for (int32 i = 0; i < FoundCharacters.Num(); i++)
			{
				FoundCharacters[i]->SetSelected();
			}
		}
		/*if (FoundBuildings.Num() > 0)
		{
			for (int32 i = 0; i < FoundBuildings.Num(); i++)
			{
				FoundBuildings[i]->SetSelected();
			}
		}*/
	}
	//TSubclassOf<APawn> CubePawn = LoadClass<APawn>(nullptr, TEXT("/Game/BP_PawnCube"));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ddd"));
	//if (FoundCharacters.Num() > 0)
	//{
	//	for (int32 i = 0; i < FoundCharacters.Num(); i++)
	//	{
	//		FoundCharacters[i]->SetDeselected();
	//	}
	//}
	//FoundCharacters.Empty();
	//GetActorsInSelectionRectangle<ASocietySimulatorCharacter>(InitialPoint, CurrentPoint, FoundCharacters, false, false);
	///*if (FoundCharacters.Num() != 0) {
	//	for (int32 i = 0; i < FoundCharacters.Num(); i++) {
	//		GEngine->AddOnScreenDebugMessage(-1, 1/60.0f, FColor::Yellow, FString::Printf(TEXT("%d"), i), false);
	//	}
	//}*/
	//if (FoundCharacters.Num() > 0) 
	//{
	//	for (int32 i = 0; i < FoundCharacters.Num(); i++) 
	//	{
	//		FoundCharacters[i]->SetSelected();
	//	}
	//}
	
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

void ASocietySimulatorHUD::ClearSelectedUnits_Implementation() {
	if (FoundCharacters.Num() > 0)
	{
		for (int32 i = 0; i < FoundCharacters.Num(); i++)
		{
			FoundCharacters[i]->SetDeselected();
		}
	}
	FoundCharacters.Empty();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("deselect"));
	ASocietySimulatorPlayerController* Control = Cast<ASocietySimulatorPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	Control->ClearUnits();
}

void ASocietySimulatorHUD::SelectSingleUnit_Implementation(AActor* Unit) {
	ASocietySimulatorCharacter* input = Cast<ASocietySimulatorCharacter>(Unit);
	input->SetSelected();
	FoundCharacters.AddUnique(input);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("single select"));
	ASocietySimulatorPlayerController* Control = Cast<ASocietySimulatorPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	Control->SingleSelect(Unit);
}