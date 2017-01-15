// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "SceneTransitionData.generated.h"


USTRUCT()
struct FSceneName
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name;
};


/**
 *
 */
UCLASS(BlueprintType)
class SPECTERFRONT_API USceneTransitionData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FSceneName> Scenes;
};
