// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DamageListenerInterface.generated.h"

UINTERFACE(Blueprintable)
class UDamageListenerInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IDamageListenerInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	// É_ÉÅÅ[ÉWÇéÛÇØÇÈ
	UFUNCTION(BlueprintImplementableEvent)
		void OnDamage(float damage, AController* instigatedBy, AActor* damageCauser);
};