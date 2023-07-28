// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SocietySimulatorHUD.h"
#include "SocietySimulatorBuilding.h"
#include "SelectedUnitsArea.h"
#include "SocietySimulatorInterface.h"

#include "SocietySimulatorPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SOCIETYSIMULATOR_API ASocietySimulatorPlayerController : public APlayerController, public ISocietySimulatorInterface
{
	GENERATED_BODY()


public:
	ASocietySimulatorPlayerController();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetLeftClickAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetRightClickAction;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	ASocietySimulatorHUD* HUDPtr;
	void ClearSelectedBuilding();
	//void AddUnitToBox(UUserWidget* input);
	void AddUnitToBox_Implementation(UUserWidget* input) override;
	void ProduceUnit_Implementation(ASocietySimulatorBuilding* Building, TSubclassOf<ASocietySimulatorCharacter> Unit) override;
	void ClearUnits();
	void SingleSelect(AActor* unit);
protected:
	void SelectionPressed();
	void SelectionReleased();
	void MoveReleased();
	
	TArray <ASocietySimulatorCharacter*> SelectedCharacters;
	ASocietySimulatorBuilding* SelectedBuilding;
	TSubclassOf<UUserWidget> SelectedUnitsAreaC;
	USelectedUnitsArea* SelectedUnitsArea;
};