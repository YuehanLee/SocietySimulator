// Fill out your copyright notice in the Description page of Project Settings.

#include "SocietySimulator.h"
#include "SocietySimulatorPlayerController.h"
#include "SocietySimulatorHUD.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ASocietySimulatorPlayerController::ASocietySimulatorPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Hand;
}

void ASocietySimulatorPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (Cast<ASocietySimulatorHUD>(GetHUD())) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("hud loaded"));
	}
	HUDPtr = Cast<ASocietySimulatorHUD>(GetHUD());
	if (HUDPtr == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("hud unseccessful"));
	}
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ASocietySimulatorPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//EnhancedInputComponent
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(SetLeftClickAction, ETriggerEvent::Started, this, &ASocietySimulatorPlayerController::SelectionPressed);
		EnhancedInputComponent->BindAction(SetLeftClickAction, ETriggerEvent::Completed, this, &ASocietySimulatorPlayerController::SelectionReleased);

		EnhancedInputComponent->BindAction(SetRightClickAction, ETriggerEvent::Started, this, &ASocietySimulatorPlayerController::MoveReleased);
	}
}

void ASocietySimulatorPlayerController::SelectionPressed()
{
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));*/
	HUDPtr->InitialPoint = HUDPtr->GetMousePos2D();
	FString x = FString::SanitizeFloat(HUDPtr->InitialPoint.X);
	FString y = FString::SanitizeFloat(HUDPtr->InitialPoint.Y);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, x);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, y);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("----------"));
	HUDPtr->bStartSelecting = true;
}

void ASocietySimulatorPlayerController::SelectionReleased()
{
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("2!"));*/
	HUDPtr->bStartSelecting = false;
	SelectedCharacters = HUDPtr->FoundCharacters;
	HUDPtr->CurrentPoint = HUDPtr->GetMousePos2D();
	FString x = FString::SanitizeFloat(HUDPtr->CurrentPoint.X);
	FString y = FString::SanitizeFloat(HUDPtr->CurrentPoint.Y);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, x);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, y);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("----------"));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("----------"));
}

void ASocietySimulatorPlayerController::MoveReleased()
{
	if (SelectedCharacters.Num() > 0) 
	{
		for (int32 i = 0; i < SelectedCharacters.Num(); i++) 
		{
			FHitResult Hit;
			GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
			FVector MoveLocation = Hit.Location;
			//UNavigationSystemV1::SimpleMoveToLocation(SelectedCharacters[i]->GetController(), MoveLocation);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedCharacters[i]->GetController(), MoveLocation);
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("----------"));
		}
	}
}
