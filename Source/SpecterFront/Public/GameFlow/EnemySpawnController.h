// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawner.h"
#include "EnemySpawnController.generated.h"

UCLASS()
class SPECTERFRONT_API AEnemySpawnController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawnController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

public: // UFUNCTION
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn")
		void BeginSpawn(const FCompleteDelegate& completeEvent);

	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void EndSpawn();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn")
		void OnComplete();

	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void AddSpawnEnemy(ABaseEnemy* spawnEnemy);

public: // UPROPERTY
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AEnemySpawner*> spawnerList;

	UPROPERTY(BlueprintReadOnly)
		TArray<ABaseEnemy*> spawnEnemies;

private:
	FCompleteDelegate completeHandler;
};
