// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyInterface.generated.h"


UINTERFACE(BlueprintType)
class UEnemyInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// すべての敵はこれを実装する
class IEnemyInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void MoveTo();

	// 出現時に呼ぶ
	UFUNCTION(BlueprintImplementableEvent)
		void Appearance();
};