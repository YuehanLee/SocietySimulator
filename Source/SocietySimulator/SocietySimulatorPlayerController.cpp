// Fill out your copyright notice in the Description page of Project Settings.

#include "SocietySimulator.h"
#include "SocietySimulatorPlayerController.h"
#include "SocietySimulatorHUD.h"
#include "SocietySimulatorResource.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationSystem.h"
#include "SelectedUnitsArea.h"
#include "Components/HorizontalBox.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ASocietySimulatorPlayerController::ASocietySimulatorPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Hand;
	static ConstructorHelpers::FClassFinder<UUserWidget> SelectedUnitsAreaFound(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/BP_SelectedUnitsArea.BP_SelectedUnitsArea_C'"));
	if (SelectedUnitsAreaFound.Class != nullptr) {
		SelectedUnitsAreaC = SelectedUnitsAreaFound.Class;
	}
}

void ASocietySimulatorPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (Cast<ASocietySimulatorHUD>(GetHUD())) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("hud loaded"));
	}
	HUDPtr = Cast<ASocietySimulatorHUD>(GetHUD());
	if (HUDPtr == nullptr) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("hud unseccessful"));
	}
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	//TSubclassOf<UUserWidget> SelectedUnitsAreaC;
	
	SelectedUnitsArea = Cast<USelectedUnitsArea>(CreateWidget(this, SelectedUnitsAreaC));
	//SelectedUnitsArea = CreateWidget<USelectedUnitsArea>(GetWorld(), USelectedUnitsArea::StaticClass());
	SelectedUnitsArea->AddToViewport();
	//SelectedUnitsArea->UnitsBox->AddChildToHorizontalBox();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("selectedunitsarea loaded"));
	
}

void ASocietySimulatorPlayerController::AddUnitToBox_Implementation(UUserWidget* input) {
	SelectedUnitsArea->UnitsBox->AddChildToHorizontalBox(input);
}

void ASocietySimulatorPlayerController::ProduceUnit_Implementation(ASocietySimulatorBuilding* Building, TSubclassOf<ASocietySimulatorCharacter> Unit)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("33"));
	Building->IsProducingUnit = true;
	Building->AddUnitToQueue(Unit);
}

void ASocietySimulatorPlayerController::ClearUnits()
{
	SelectedCharacters.Empty();
}

void ASocietySimulatorPlayerController::SingleSelect(AActor* unit)
{
	ASocietySimulatorCharacter* input = Cast<ASocietySimulatorCharacter>(unit);
	SelectedCharacters.AddUnique(input);
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

void ASocietySimulatorPlayerController::ClearSelectedBuilding() {
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, "--------");
	if (SelectedBuilding) {
		SelectedBuilding->SetDeselected();
		SelectedBuilding = NULL;
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "--------");
	}
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, "--------");
}

void ASocietySimulatorPlayerController::SelectionPressed()
{
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));*/
	HUDPtr->InitialPoint = HUDPtr->GetMousePos2D();
	//FString x = FString::SanitizeFloat(HUDPtr->InitialPoint.X);
	//FString y = FString::SanitizeFloat(HUDPtr->InitialPoint.Y);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, x);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, y);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("----------"));
	HUDPtr->bStartSelecting = true;
	ClearSelectedBuilding();
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "--------");
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
	//FVector MoveLocation = Hit.Location;
	AActor* CurrentSelectedBuilding = Hit.GetActor();
	//GetClass(selectedBuilding)
	ASocietySimulatorBuilding* SB = Cast<ASocietySimulatorBuilding>(CurrentSelectedBuilding);
	if (SB) {
		SB->SetSelected();
		SelectedBuilding = SB;
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "--------");
	}
	else {
	}
}

void ASocietySimulatorPlayerController::SelectionReleased()
{
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("2!"));*/
	HUDPtr->bStartSelecting = false;
	SelectedCharacters = HUDPtr->FoundCharacters;
	if (SelectedCharacters.Num()) {
		ClearSelectedBuilding();
	}
	for (int32 i = 0; i < SelectedCharacters.Num(); i++) {
		//SelectedUnitsArea->UnitsBox->AddChildToHorizontalBox(SelectedCharacters[i]->SelectedUnitWidget);
		//GEngine->AddOnScreenDebugMessage(-1, 1 / 60.0f, FColor::Yellow, FString::Printf(TEXT("%d"), i), false);
	}
	
	HUDPtr->CurrentPoint = HUDPtr->GetMousePos2D();
	//FString x = FString::SanitizeFloat(HUDPtr->CurrentPoint.X);
	//FString y = FString::SanitizeFloat(HUDPtr->CurrentPoint.Y);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, x);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, y);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("----------"));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("----------"));
}

void ASocietySimulatorPlayerController::MoveReleased()
{
	FHitResult HitN;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitN);
	AActor* SelectedResource = HitN.GetActor();
	ASocietySimulatorResource* SR = Cast<ASocietySimulatorResource>(SelectedResource);
	if (SR) {
		//SR->IsWorking();
		if (SelectedCharacters.Num() > 0) {
			//SR->isWorking() = true;
			for (int32 i = 0; i < SelectedCharacters.Num(); i++)
			{
				SelectedCharacters[i]->IsWorking(SR);
				//FHitResult Hit;
				//GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
				//FVector MoveLocation = HitN.Location;
				//UNavigationSystemV1::SimpleMoveToLocation(SelectedCharacters[i]->GetController(), MoveLocation);
				//UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedCharacters[i]->GetController(), MoveLocation);
				//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("----------"));
			}
		}
	}
	else if(SelectedCharacters.Num() > 0)
	{
		for (int32 i = 0; i < SelectedCharacters.Num(); i++) 
		{
			//FHitResult Hit;
			//GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
			FVector MoveLocation = HitN.Location;
			//UNavigationSystemV1::SimpleMoveToLocation(SelectedCharacters[i]->GetController(), MoveLocation);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedCharacters[i]->GetController(), MoveLocation);
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("----------"));
		}
	}
}
