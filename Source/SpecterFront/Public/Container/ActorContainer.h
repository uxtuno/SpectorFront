// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Array.h"
#include "BaseEnemy.h"
#include "ActorContainer.generated.h"

/**	
 *	
 */
UCLASS(Blueprintable, BlueprintType)
class SPECTERFRONT_API UActorContainer : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		TArray<AActor*> actors;

private: // UFUNCTION
	// “G‚ð’Ç‰Á
	UFUNCTION(BlueprintCallable, Category = "EnemySpawner", meta = (BlueprintProtected, AllowPrivteAccess = "true"))
		void AddActor(AActor* actor);
};
