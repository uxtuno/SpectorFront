// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SPECTERFRONT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

public:
	virtual void Tick(float deltaTime) override;
	virtual void BeginPlay() override;

};
