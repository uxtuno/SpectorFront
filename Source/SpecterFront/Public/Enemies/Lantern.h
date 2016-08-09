// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseEnemy.h"
#include "Lantern.generated.h"

/**
 *
 */
UCLASS()
class SPECTERFRONT_API ALantern : public ABaseEnemy
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float moveSpeed;
};
