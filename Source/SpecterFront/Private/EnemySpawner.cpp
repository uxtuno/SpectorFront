// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "BaseEnemy.h"
#include "ActionPhaseController.h"
#include "EnemySpawner.h"
#include "EnemySpawnController.h"


// 生成
// owner : 生成元
void AEnemySpawner::BeginSpawn_Implementation(AEnemySpawner* spawner)
{
	// スポーン実行中
	if (isSpawing)
		return;

	this->spawner = spawner;

	isSpawing = true;
	OnBeginSpawn();
}

void AEnemySpawner::FinishSpawn()
{
	// 全ての敵の通知先から自身を削除
	for (auto enemy : spawnedEnemies)
	{
		if (enemy == nullptr)
			continue;

		enemy->RemoveObserver(this);
	}

	if (spawner != nullptr)
	{
		spawner->TakeOverEnemies(spawnedEnemies);
	}

	isSpawing = false;
}

void AEnemySpawner::OnEnemyDie_Implementation(ABaseEnemy* enemy)
{
	spawnedEnemies.Remove(enemy);
}

void AEnemySpawner::EnemySpawnRelative(const FVector & relativeLocation)
{
	EnemySpawn(GetActorLocation() + relativeLocation);
}

void AEnemySpawner::EnemySpawn(const FVector & location)
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
	spawnedEnemies.Add(enemy);
}

int32 AEnemySpawner::GetSpawnedEnemyCount()
{
	return spawnedEnemies.Num();
}

void AEnemySpawner::OnBeginSpawn_Implementation()
{
	EnemySpawnRelative(FVector(0.0f, 0.0f, 0.0f));
}

void AEnemySpawner::TakeOverEnemies(TArray<ABaseEnemy*> enemies)
{
	spawnedEnemies.Append(enemies);
}

