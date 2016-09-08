// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "MyPlayerController.h"
#include "PlayerCharacter.h"
#include "Engine/LocalPlayer.h"

void AMyPlayerController::BeginPlay()
{
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FViewport* Viewport = LocalPlayer->ViewportClient->Viewport;
		if (Viewport)
		{
			FVector2D ViewportSize;
			LocalPlayer->ViewportClient->GetViewportSize(ViewportSize);
			const int32 X = static_cast<int32>(ViewportSize.X * 0.5f);
			const int32 Y = static_cast<int32>(ViewportSize.Y * 0.5f);

			Viewport->SetMouse(X, Y);
		}
	}
}

void AMyPlayerController::Tick(float deltaTime)
{
	float x;
	float y;
	this->GetMousePosition(x, y);

	auto player = Cast<APlayerCharacter>(this->GetPawn());

	player->SetReticleLocation(FVector2D(x, y));


}


