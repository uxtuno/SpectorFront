// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "AbstractEnemySpawner.h"


// Sets default values
AAbstractEnemySpawner::AAbstractEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAbstractEnemySpawner::TriggerSpawn_Implementation(FFinishSpawn callback, UActorContainer* container)
{
	if (isSpawning)
	{
		return;
	}

	finishSpawnHandler = callback;
	isSpawning = true;

	BeginSpawn();
}

void AAbstractEnemySpawner::Finish()
{
	isSpawning = false;

	// èIóπí ím
	finishSpawnHandler.finishSpawnDelegate.ExecuteIfBound();
}
