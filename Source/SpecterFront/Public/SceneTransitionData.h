// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "SceneTransitionData.generated.h"


USTRUCT()
struct FSceneData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name;

	// ステージかどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isStage;
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
		TArray<FSceneData> Scenes;

	UFUNCTION(BlueprintCallable, Category = "Scene")
		int32 FindScene(FString sceneName) const;
};
