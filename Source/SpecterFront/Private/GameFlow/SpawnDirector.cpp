// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "SpawnDirector.h"


// Sets default values
ASpawnDirector::ASpawnDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// 生成
// owner : 生成元
void ASpawnDirector::Begin_Implementation(FFinishSpawn callback, UEnemyContainer* spawnedEnemies)
{
	// スポーン実行中
	if (isSpawing)
		return;

	finishSpawnHandler = callback.finishSpawnDelegate;

	if (spawnedEnemies != nullptr)
	{
		this->spawnedEnemies = spawnedEnemies;
	}

	isSpawing = true;
	OnBeginSpawn();
}

void ASpawnDirector::OnBeginSpawn_Implementation()
{
}

