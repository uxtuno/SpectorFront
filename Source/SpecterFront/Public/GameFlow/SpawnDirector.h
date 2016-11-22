// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnerInterface.h"
#include "AbstractEnemySpawner.h"
#include "SpawnDirector.generated.h"

UCLASS()
class SPECTERFRONT_API ASpawnDirector : public AAbstractEnemySpawner
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnDirector();

	// 敵の生成開始時に呼び出される。Blueprintでオーバーライドして処理を実装する
	UFUNCTION(BlueprintNativeEvent, Category = "EnemySpawn", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		void OnBeginSpawn();

	// 起動するスポーナー
	UPROPERTY(EditAnywhere, Category = "EnemySpawner")
		TArray<TSubclassOf<ISpawnerInterface>> spawners;
};
