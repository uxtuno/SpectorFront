// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "Engine.h"
#include "MyBlueprintFunctionLibrary.h"


UObject* UMyBlueprintFunctionLibrary::CreateObject(UObject* WorldContextObject, TSubclassOf<UObject> type)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	return NewObject<UObject>(WorldContextObject, type);
}

UObject* UMyBlueprintFunctionLibrary::FindUniqueActorOfClass(UObject* WorldContextObject, TSubclassOf<AActor> type)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	TActorIterator<AActor> ait(World, type);
	if (!ait || ait.GetProgressNumerator() != 1)
	{
		return nullptr;
	}

	return *ait;
}