// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "AbstractEnemySpawner.h"


// Sets default values
AAbstractEnemySpawner::AAbstractEnemySpawner()
	: allEnemies(nullptr)
	, isSpawning(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAbstractEnemySpawner::OnEnemyDie_Implementation(TScriptInterface<IEnemyInterface>& enemy)
{
	allEnemies->actors.Remove(Cast<AActor>(enemy.GetObjectRef()));
	NotifiRemoveEnemy();
}

void AAbstractEnemySpawner::TriggerSpawn_Implementation(AAbstractEnemySpawner* parent, FFinishSpawn callback, UActorContainer* allEnemies)
{
	if (isSpawning)
	{
		return;
	}

	this->allEnemies = allEnemies;
	this->parent = parent;
	finishSpawnHandler = callback;
	isSpawning = true;

	BeginSpawn();
}

int32 AAbstractEnemySpawner::GetSpawnedEnemyCount() const
{
	return managedEnemyCount;
}

void AAbstractEnemySpawner::Finish()
{
	if (!isSpawning)
	{
		return;
	}

	isSpawning = false;

	// 終了通知
	finishSpawnHandler.finishSpawnDelegate.ExecuteIfBound();
}

void AAbstractEnemySpawner::NotifiAddEnemy()
{
	if (parent == nullptr)
		return;

	++managedEnemyCount;

	// 子から親へ順次呼び出していく
	parent->NotifiAddEnemy();
}

void AAbstractEnemySpawner::NotifiRemoveEnemy()
{
	if (parent == nullptr)
		return;

	--managedEnemyCount;

	// 子から親へ順次呼び出していく
	parent->NotifiRemoveEnemy();
}
