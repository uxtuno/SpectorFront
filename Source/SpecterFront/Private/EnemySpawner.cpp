// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "BaseEnemy.h"
#include "EnemySpawner.h"
#include "EnemySpawnController.h"


void AEnemySpawner::BeginSpawn_Implementation(AEnemySpawnController* spawnController)
{
	this->spawnController = spawnController;
	FVector location = GetActorLocation();
	FRotator rotation = GetActorRotation();
	FActorSpawnParameters p;
	p.bNoCollisionFail = true;
	ABaseEnemy* enemy = Cast<ABaseEnemy>(GetWorld()->SpawnActor(spawnEnemy, &location, &rotation, p));
	enemy->SetSpawnController(spawnController);

	if (spawnController == nullptr)
	{
		return;
	}

	enemy->SpawnDefaultController();
	this->spawnController->AddSpawnEnemy(enemy);
}

void AEnemySpawner::FinishSpawn()
{
	spawnController->OnFinishSpawn();
}

