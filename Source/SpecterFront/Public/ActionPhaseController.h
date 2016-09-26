// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ActionPhaseController.generated.h"

UCLASS()
class SPECTERFRONT_API AActionPhaseController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActionPhaseController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

public: // UFUNCTION
	// アクションフェーズ終了時に呼び出す
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn")
		void Finish();

	// Spawnerからのスポーン終了通知を受け取る
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn")
		void OnFinishSpawn();

	// スポーンした敵をActionPhaseの管理下に置く
	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void AppendSpawnEnemies(TArray<class ABaseEnemy*> enemies);
	// スポーンした敵をActionPhaseの管理下に置く
	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void AddSpawnEnemy(class ABaseEnemy* enemy);

public: // UPROPERTY
	UPROPERTY(BlueprintReadOnly, Category = "EnemySpawn")
		TArray<class ABaseEnemy*> managedEnemies;
};
