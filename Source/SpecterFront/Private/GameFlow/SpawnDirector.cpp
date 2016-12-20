// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "SpawnDirector.h"
//#include "Runtime/Engine/Classes/Components/BillboardComponent.h"
//#include "Runtime/Engine/Classes/Components/ArrowComponent.h"


// Sets default values
ASpawnDirector::ASpawnDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// スプライトを削除
	//GetSpriteComponent()->DestroyComponent();
	//GetArrowComponent()->DestroyComponent();
}

