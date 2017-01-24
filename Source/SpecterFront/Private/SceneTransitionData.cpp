// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "SceneTransitionData.h"

int32 USceneTransitionData::FindScene(FString sceneName) const
{
	int index = 0;
	for (auto element : Scenes)
	{
		if (element.name == sceneName)
		{
			return index;
		}
		++index;
	}

	return -1;
}
