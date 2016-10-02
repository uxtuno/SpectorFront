// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "BaseEnemy.h"
#include "ActionPhaseController.h"


// Sets default values
AActionPhaseController::AActionPhaseController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActionPhaseController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActionPhaseController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AActionPhaseController::Finish_Implementation()
{
	for (auto enemy : managedEnemies)
	{
		enemy->RemoveObserver(this);
	}
}

void AActionPhaseController::OnFinishSpawn_Implementation()
{
}

void AActionPhaseController::AppendSpawnEnemies(const TArray<ABaseEnemy*>& enemies)
{
	managedEnemies.Append(enemies);
	for (auto enemy : managedEnemies)
	{
		FScriptDelegate observer;
		observer.BindUFunction(this, "OnEnemyDie");
		enemy->AddObserver(observer);
	}
}

void AActionPhaseController::AddSpawnEnemy(ABaseEnemy * enemy)
{
	managedEnemies.Add(enemy);
}

void AActionPhaseController::OnEnemyDie_Implementation(ABaseEnemy * enemy)
{
	managedEnemies.Remove(enemy);
}
