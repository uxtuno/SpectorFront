// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TargetPoint.h"
#include "BaseEnemy.h"
#include "EnemySpawner.generated.h"

// 敵の生成が終了したことを通知する
DECLARE_DYNAMIC_DELEGATE(FCompleteDelegate);

/**
 * 敵の出現位置を指定するためのオブジェクト
 */
UCLASS(Blueprintable, BlueprintType)
class SPECTERFRONT_API AEnemySpawner : public ATargetPoint
{
	GENERATED_BODY()

public:
	// 生成。ブループリント側でオーバーライドする場合はオーバーライド元も呼ぶこと
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn")
		void Spawn(AEnemySpawnController* spawnController);

public:
	// スポーンを管理するオブジェクト
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AEnemySpawnController* spawnController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ABaseEnemy> spawnEnemy;

	//UPROPERTY(BlueprintReadWrite)
	//	FCompleteDelegate completeEvent;

public:
	// 現在のスポーナーから制御を移す際に呼び出す
	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void Complete();
};
