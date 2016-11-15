// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Array.h"
#include "BaseEnemy.h"
#include "EnemyContainer.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class SPECTERFRONT_API UEnemyContainer : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		TArray<ABaseEnemy*> enemies;

private: // UFUNCTION
	// “G‚ð’Ç‰Á
	UFUNCTION(BlueprintCallable, Category = "EnemySpawner", meta = (BlueprintProtected, AllowPrivteAccess = "true"))
		void AddEnemy(ABaseEnemy* enemy);
};
