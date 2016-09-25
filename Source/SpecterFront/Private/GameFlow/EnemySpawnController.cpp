// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "BaseEnemy.h"
#include "EnemySpawnController.h"


// Sets default values
AEnemySpawnController::AEnemySpawnController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawnController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemySpawnController::BeginSpawnSequence_Implementation(const FFinishSpawnDelegate& finishEvent)
{
	completeHandler = finishEvent;
}

void AEnemySpawnController::FinishSpawnSequence()
{
	completeHandler.ExecuteIfBound();
}

void AEnemySpawnController::OnEnemyDie(ABaseEnemy * enemy)
{
	spawnEnemies.Remove(enemy);
}

void AEnemySpawnController::OnFinishSpawn_Implementation()
{
}

void AEnemySpawnController::AddSpawnEnemy(ABaseEnemy* spawnEnemy)
{
	spawnEnemies.Add(spawnEnemy);
}

// Called every frame
void AEnemySpawnController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

