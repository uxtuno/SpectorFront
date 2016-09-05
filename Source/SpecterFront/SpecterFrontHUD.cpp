// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SpecterFront.h"
#include "SpecterFrontHUD.h"
#include "Engine/Canvas.h"
#include "Engine.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "PlayerCharacter.h"

ASpecterFrontHUD::ASpecterFrontHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshiarTexObj.Object;
}


void ASpecterFrontHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair
	UWorld* const world = GetWorld();

	APlayerCharacter* player = nullptr;

	// ÉJÉÅÉâê›íË
	for (TActorIterator<APlayerCharacter> Itr(world); Itr; ++Itr)
	{
		if (Itr->ActorHasTag("Player"))
		{
			player = Cast<APlayerCharacter>(Itr->GetActorClass());
			break;
		}
	}

	if (player == nullptr)
		return;

	//// find center of the Canvas
	const FVector2D Center(player->GetReticleLocation().X, player->GetReticleLocation().Y);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y));

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

