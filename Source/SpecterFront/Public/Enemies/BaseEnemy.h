// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyCharacter.h"
#include "BaseEnemy.generated.h"

UCLASS(abstract)
class SPECTERFRONT_API ABaseEnemy : public AMyCharacter
{
	GENERATED_BODY()

public:
	virtual void Wait(float tick);
};
