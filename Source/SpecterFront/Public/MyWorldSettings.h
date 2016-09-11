// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/WorldSettings.h"
#include "MyWorldSettings.generated.h"

/**
 *
 */
UCLASS()
class SPECTERFRONT_API AMyWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
		TArray<class ABaseEnemy*> enemies;

};
