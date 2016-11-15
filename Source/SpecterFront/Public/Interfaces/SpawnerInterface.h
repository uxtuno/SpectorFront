// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "SpawnableInterface.h"
#include "SpawnerInterface.generated.h"


UINTERFACE(BlueprintType)
class USpawnerInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// 生成を担当するオブジェクト
class ISpawnerInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	// 生成開始
	UFUNCTION(BlueprintImplementableEvent)
		void Begen(FFinishSpawn callBack, UEnemyContainer* spawnedEnemies);
};