// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "BaseEnemy.h"
#include "ActionPhaseController.h"
#include "EnemySpawner.h"
#include "EnemySpawnController.h"


void AEnemySpawner::BeginSpawn_Implementation(AActionPhaseController* spawnController)
{
	if (spawnEnemyType == nullptr)
	{
		return;
	}

	this->spawnController = spawnController;
	FVector location = GetActorLocation();
	FRotator rotation = GetActorRotation();
	FActorSpawnParameters p;
	p.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ABaseEnemy* enemy = Cast<ABaseEnemy>(GetWorld()->SpawnActor(spawnEnemyType, &location, &rotation, p));
	enemy->SetSpawnController(spawnController);

	if (spawnController == nullptr)
	{
		return;
	}

	enemy->SpawnDefaultController();

	if (isIgnoreble)
	{
		this->spawnController->AddSpawnEnemy(enemy);
	}
	else
	{
		spawnedEnemies.Add(enemy);
	}
}

void AEnemySpawner::FinishSpawn()
{
	spawnController->OnFinishSpawn();
}

