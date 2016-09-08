// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "MyPlayerController.h"
#include "PlayerCharacter.h"


void AMyPlayerController::Tick(float deltaTime)
{
	float x;
	float y;
	this->GetMousePosition(x, y);

	auto player = Cast<APlayerCharacter>(this->GetPawn());

	player->SetReticleLocation(FVector2D(x, y));
}


