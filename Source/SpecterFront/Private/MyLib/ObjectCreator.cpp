// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "Engine.h"
#include "ObjectCreator.h"


UObject* UObjectCreator::CreateObject(UObject* WorldContextObject, TSubclassOf<UObject> type)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	return NewObject<UObject>(WorldContextObject, type);
}