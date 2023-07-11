// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SocietySimulatorHUD.h"
#include "SocietySimulatorPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SOCIETYSIMULATOR_API ASocietySimulatorPlayerController : public APlayerController
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
protected:
	void SelectionPressed();
	void SelectionReleased();
	void MoveReleased();
	TArray <ASocietySimulatorCharacter*> SelectedCharacters;
};
