// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "BaseEnemy.h"
#include "EnemySpawner.h"
#include "EnemySpawnController.h"


void AEnemySpawner::Spawn_Implementation(AEnemySpawnController* spawnController)
{
	this->spawnController = spawnController;
	FVector location = GetActorLocation();
	FRotator rotation = GetActorRotation();
	FActorSpawnParameters p;
	p.bNoCollisionFail = true;
	ABaseEnemy* enemy = Cast<ABaseEnemy>(GetWorld()->SpawnActor(spawnEnemy, &location, &rotation, p));
	
	if (spawnController == nullptr)
	{
		return;
	}

	enemy->SpawnDefaultController();
	this->spawnController->AddSpawnEnemy(enemy);
}

void AEnemySpawner::Complete()
{
	spawnController->OnComplete();
}

