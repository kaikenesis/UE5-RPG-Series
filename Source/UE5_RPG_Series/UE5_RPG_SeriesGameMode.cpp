// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_RPG_SeriesGameMode.h"
#include "UE5_RPG_SeriesPlayerController.h"
#include "UE5_RPG_SeriesCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE5_RPG_SeriesGameMode::AUE5_RPG_SeriesGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUE5_RPG_SeriesPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}