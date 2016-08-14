// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "BaseEnemy.generated.h"

UCLASS(abstract)
class SPECTERFRONT_API ABaseEnemy : public APawn
{
	GENERATED_BODY()

public:
	virtual void Wait(float tick);
};
