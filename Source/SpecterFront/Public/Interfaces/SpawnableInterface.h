// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpawnableInterface.generated.h"




UINTERFACE(Blueprintable)
class USpawnableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ISpawnableInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	// ÉXÉ|Å[Éì
	UFUNCTION(BlueprintImplementableEvent)
		void BeginSpawn();
};