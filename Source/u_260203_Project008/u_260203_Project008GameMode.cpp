// Copyright Epic Games, Inc. All Rights Reserved.

#include "u_260203_Project008GameMode.h"
#include "u_260203_Project008Character.h"
#include "UObject/ConstructorHelpers.h"
#include "NewGameState.h"

Au_260203_Project008GameMode::Au_260203_Project008GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	GameStateClass = ANewGameState::StaticClass();
}
