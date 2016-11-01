// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpawnableInterface.generated.h"


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

UINTERFACE(Blueprintable)
class USpawnableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ISpawnableInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	// スポーン
	UFUNCTION(BlueprintImplementableEvent)
		void BeginSpawn(FFinishSpawn spawner, const TArray<ABaseEnemy*>& spawnEnemies);
};