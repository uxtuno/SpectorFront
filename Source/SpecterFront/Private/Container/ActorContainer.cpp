// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "ActorContainer.h"


void UActorContainer::AddActor(AActor* actor)
{
	actors.Add(actor);
}
