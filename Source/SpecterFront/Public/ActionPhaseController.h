// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawner.h"
#include "ActionPhaseController.generated.h"

UCLASS()
class SPECTERFRONT_API AActionPhaseController : public AEnemySpawner
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActionPhaseController();

};
