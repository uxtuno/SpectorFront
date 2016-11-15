// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "ObjectCreator.h"


UObject* UObjectCreator::NewObject(TSubclassOf<UObject> type)
{
	return ::NewObject<UObject>(type->GetClass());
}