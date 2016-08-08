// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SpecterFront.h"
#include "SpecterFrontGameMode.h"
#include "SpecterFrontHUD.h"
#include "SpecterFrontCharacter.h"

ASpecterFrontGameMode::ASpecterFrontGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/BluePrints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASpecterFrontHUD::StaticClass();
}
