// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "DebugLog.h"
#include "Engine.h"

namespace MyDebugUtility
{
	void LogToScreen(const FString& message)
	{
		if (GEngine != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor(200, 200, 200), message);
		}
	}
}
