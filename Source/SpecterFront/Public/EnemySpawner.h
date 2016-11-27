// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TargetPoint.h"
#include "AbstractEnemySpawner.h"
#include "BaseEnemy.h"
#include "Container/ActorContainer.h"
#include "SpawnerInterface.h"
#include "EnemySpawner.generated.h"


/**
 * 敵の出現位置を指定するためのオブジェクト
 */
UCLASS(Blueprintable, BlueprintType)
class SPECTERFRONT_API AEnemySpawner : public AAbstractEnemySpawner
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private: // UPROPERTY

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ABaseEnemy> spawnEnemyType;

public:

	// 敵を生成する
	// relativeLocation : 自身を中心とした相対的な位置
	UFUNCTION(BlueprintCallable, Category = "EnemySpawn", meta = (BlueprintProtected))
		void EnemySpawnRelative(const FVector relativeLocation);
	// 敵を生成する
	UFUNCTION(BlueprintCallable, Category = "EnemySpawn", meta = (BlueprintProtected))
		void EnemySpawn(const FVector location);

};
