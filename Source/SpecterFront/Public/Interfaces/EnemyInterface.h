// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyInterface.generated.h"


UINTERFACE(BlueprintType)
class UEnemyInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// ‚·‚×‚Ä‚Ì“G‚Í‚±‚ê‚ğÀ‘•‚·‚é
class IEnemyInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void MoveTo();

	// oŒ»‚ÉŒÄ‚Ô
	UFUNCTION(BlueprintImplementableEvent)
		void Appearance();

	// €–S‚É’Ê’m‚·‚éæ‚ğ“o˜^
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
		void AddObserver(UObject* observer);

	// ’Ê’mæ‚ğíœ
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
		void RemoveObserver(UObject* observer);
};