// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "SpawnDirector.h"

#ifdef WITH_EDITOR
#include "Runtime/Engine/Classes/Components/BillboardComponent.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"
#endif

// Sets default values
ASpawnDirector::ASpawnDirector()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// スプライトを削除
#ifdef WITH_EDITOR
	//GetSpriteComponent()->DestroyComponent();
	GetSpriteComponent()->SetVisibility(false, false);
	GetArrowComponent()->SetVisibility(false, false);
#endif
}
