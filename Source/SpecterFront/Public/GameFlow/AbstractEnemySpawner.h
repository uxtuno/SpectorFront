// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "SpawnableInterface.h"
#include "ActorContainer.h"
#include "AbstractEnemySpawner.generated.h"

// 敵の生成が終了したことを通知する
DECLARE_DYNAMIC_DELEGATE(FFinishSpawnDelegate);

// 引数構造体
USTRUCT(BlueprintType)
struct FFinishSpawn
{
	GENERATED_BODY()

public:
	// 省略したいデリゲート
	UPROPERTY(BlueprintReadWrite)
		FFinishSpawnDelegate finishSpawnDelegate;

	FFinishSpawn()
		: finishSpawnDelegate()
	{
	}
};

UCLASS(abstract)
class SPECTERFRONT_API AAbstractEnemySpawner : public ATargetPoint
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbstractEnemySpawner();

	// スポーンを開始する
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemySpawner")
		void TriggerSpawn(FFinishSpawn callback, UActorContainer* container);

	// スポーン開始時に呼ばれる
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "EnemySpawner")
		void BeginSpawn();

protected:
	// スポーン終了を宣言し、再びスポーン開始を可能とする
	UFUNCTION(BlueprintCallable, Category = "EnemySpawner")
		void Finish();

	// スポーン終了時に呼ばれる
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "EnemySpawner")
		void FinishSpawn();

	// 自身が管理する敵
	UPROPERTY(BlueprintReadOnly, meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		class UActorContainer* spawnedEnemies;

private:
	// スポーン中、このフラグがtrueの間は、TriggerSpawnを呼ばれてもスポーンが行われない
	UPROPERTY(BlueprintReadOnly, meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		bool isSpawning;

	// スポーン終了を通知する
	FFinishSpawn finishSpawnHandler;
};
