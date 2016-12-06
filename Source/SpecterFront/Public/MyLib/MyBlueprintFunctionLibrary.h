// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SPECTERFRONT_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Create Object From Blueprint", CompactNodeTitle = "Create", Keywords = "new create blueprint", DeterminesOutputType = "type"), Category = Game)
		static UObject* CreateObject(UObject* WorldContextObject, TSubclassOf<UObject> type);

	// 現在のレベルに存在する唯一のアクターを検索
	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", Keywords = "Get All Actor Class Unique", DeterminesOutputType = "type"), Category = Game)
		static UObject* FindUniqueActorOfClass(UObject* WorldContextObject, TSubclassOf<AActor> type);
};
