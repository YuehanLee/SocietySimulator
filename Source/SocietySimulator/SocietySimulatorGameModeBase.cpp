// Copyright Epic Games, Inc. All Rights Reserved.


#include "SocietySimulatorGameModeBase.h"
#include "SocietySimulatorPlayerController.h"


ASocietySimulatorGameModeBase::ASocietySimulatorGameModeBase()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASocietySimulatorPlayerController::StaticClass();

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BP_RTS"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}