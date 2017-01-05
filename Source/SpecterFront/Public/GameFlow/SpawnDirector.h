// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnerInterface.h"
#include "AbstractEnemySpawner.h"
#include "SpawnDirector.generated.h"

USTRUCT(Blueprintable)
struct FSpawninfomation
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		class AAbstractEnemySpawner* spawner;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UBaseCameraController> cameraController;
};

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



