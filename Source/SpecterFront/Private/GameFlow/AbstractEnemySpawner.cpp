// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "AbstractEnemySpawner.h"


// Sets default values
AAbstractEnemySpawner::AAbstractEnemySpawner()
	: allEnemies(nullptr)
	, isSpawning(false)
	, isGenerating(false)
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
	isGenerating = true;

	BeginSpawn();
}

int32 AAbstractEnemySpawner::GetSpawnedEnemyCount() const
{
	return managedEnemyCount;
}

void AAbstractEnemySpawner::EndSpawn()
{
	if (!isSpawning)
	{
		return;
	}

	isGenerating = false;

	// BPに対して終了通知
	OnEndSpawn();
}

void AAbstractEnemySpawner::Finish()
{
	if (!isSpawning)
	{
		return;
	}

	isSpawning = false;

	// 親に対して終了通知
	finishSpawnHandler.finishSpawnDelegate.ExecuteIfBound();
}

void AAbstractEnemySpawner::NotifiAddEnemy()
{
	++managedEnemyCount;

	if (parent == nullptr)
		return;

	// 子から親へ順次呼び出していく
	parent->NotifiAddEnemy();
}

void AAbstractEnemySpawner::NotifiRemoveEnemy()
{
	--managedEnemyCount;

	if (parent == nullptr)
		return;

	// 子から親へ順次呼び出していく
	parent->NotifiRemoveEnemy();
}
