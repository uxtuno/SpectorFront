// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ObjectCreator.generated.h"

/**
 * 
 */
UCLASS()
class SPECTERFRONT_API UObjectCreator : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Utility", meta = (DeterminesOutputType = "type"))
		static UObject* NewObject(TSubclassOf<UObject> type);
};
