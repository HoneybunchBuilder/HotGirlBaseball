// Copyright Epic Games, Inc. All Rights Reserved.

#include "HotGirlBaseBallGameMode.h"
#include "HotGirlBaseBallCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHotGirlBaseBallGameMode::AHotGirlBaseBallGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
