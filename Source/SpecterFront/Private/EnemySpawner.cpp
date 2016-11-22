// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "Core.h"
#include "BaseEnemy.h"
#include "ActionPhaseController.h"
#include "EnemySpawner.h"

#include "EnemySpawnController.h"


void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemySpawner::EnemySpawnRelative(const FVector relativeLocation)
{
 	EnemySpawn(GetActorLocation() + relativeLocation);
}

void AEnemySpawner::EnemySpawn(const FVector location)
{
	if (spawnEnemyType == nullptr)
		return;

	FRotator rotation = GetActorRotation();

	FActorSpawnParameters p;
	p.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	auto enemy = GetWorld()->SpawnActor(spawnEnemyType, &location, &rotation, p);
	auto ienemy = Cast<IEnemyInterface>(enemy);

	if (enemy == nullptr)
	{
		return;
	}

	Cast<APawn>(enemy)->SpawnDefaultController();

	ienemy->Execute_AddObserver(enemy, this);
	NotifiAddEnemy();
}

int32 AEnemySpawner::GetSpawnedEnemyCount() const
{
	return spawnedEnemies.Num();
}

