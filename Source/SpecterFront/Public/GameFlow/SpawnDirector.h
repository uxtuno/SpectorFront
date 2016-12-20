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
	ASpawnDirector();

	// 起動するスポーナー
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemySpawner")
		TArray<AAbstractEnemySpawner*> spawners;
};
