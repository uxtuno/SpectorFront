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
	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Create Object From Blueprint", CompactNodeTitle = "Create", Keywords = "new create blueprint", DeterminesOutputType = "type"), Category = Game)
		static UObject* CreateObject(UObject* WorldContextObject, TSubclassOf<UObject> type);
};
