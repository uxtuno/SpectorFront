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

	spawnedEnemies = NewObject<UActorContainer>();
}

void AEnemySpawner::OnEnemyDie_Implementation(ABaseEnemy* enemy)
{
	UE_LOG(LogTemp, Warning, TEXT("enemies : %d"), spawnedEnemies->actors.Num());
	spawnedEnemies->actors.Remove(enemy);
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
	ABaseEnemy* enemy = Cast<ABaseEnemy>(GetWorld()->SpawnActor(spawnEnemyType, &location, &rotation, p));

	if (enemy == nullptr)
	{
		return;
	}

	enemy->SpawnDefaultController();

	FScriptDelegate enemyDieHandler;
	enemyDieHandler.BindUFunction(this, "OnEnemyDie");
	enemy->AddObserver(enemyDieHandler);
	spawnedEnemies->actors.Add(enemy);
}

int32 AEnemySpawner::GetSpawnedEnemyCount() const
{
	return spawnedEnemies->actors.Num();
}

void AEnemySpawner::OnBeginSpawn_Implementation()
{
	EnemySpawnRelative(FVector(0.0f, 0.0f, 0.0f));
}

void AEnemySpawner::TakeOverEnemies(TArray<ABaseEnemy*> enemies)
{
	spawnedEnemies->actors.Append(enemies);
}

