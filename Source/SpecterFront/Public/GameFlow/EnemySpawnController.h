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
	// 敵の生成制御を開始する
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn")
		void BeginSpawnSequence(const FFinishSpawnDelegate& finishEvent);

	// 生成終了を通知する
	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void FinishSpawnSequence();

	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void OnEnemyDie(class ABaseEnemy* enemy);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn")
		void OnFinishSpawn();

	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void AddSpawnEnemy(ABaseEnemy* spawnEnemy);

public: // UPROPERTY
	UPROPERTY(BlueprintReadOnly, Meta = (ExposeOnSpawn = true))
		TArray<class AEnemySpawner*> spawnerList;

	UPROPERTY(BlueprintReadOnly)
		TArray<ABaseEnemy*> spawnEnemies;

private:
	FFinishSpawnDelegate completeHandler;
};
