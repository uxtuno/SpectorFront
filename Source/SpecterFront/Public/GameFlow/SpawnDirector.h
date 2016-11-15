// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnerInterface.h"
#include "SpawnDirector.generated.h"

UCLASS()
class SPECTERFRONT_API ASpawnDirector : public AActor, public ISpawnerInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnDirector();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn")
		void Begin(FFinishSpawn callback, UEnemyContainer* spawnedEnemies);

	// 敵の生成開始時に呼び出される。Blueprintでオーバーライドして処理を実装する
	UFUNCTION(BlueprintNativeEvent, Category = "EnemySpawn", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		void OnBeginSpawn();

	// 起動するスポーナー
	UPROPERTY(EditAnywhere, Category = "EnemySpawner")
		TArray<TSubclassOf<ISpawnerInterface>> spawners;

	// スポーン状態
	UPROPERTY(BlueprintReadOnly, meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		bool isSpawing;

	// 制御を終了するときに呼び出すデリゲート
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FFinishSpawnDelegate finishSpawnHandler;

	// 自身が管理する敵
	UPROPERTY(BlueprintReadOnly)
		UEnemyContainer* spawnedEnemies;
};
