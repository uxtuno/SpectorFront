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

void AEnemySpawnController::BeginSpawn_Implementation(const FCompleteDelegate& completeEvent)
{
	completeHandler = completeEvent;
}

void AEnemySpawnController::EndSpawn()
{
	completeHandler.ExecuteIfBound();
}

void AEnemySpawnController::OnComplete_Implementation()
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

