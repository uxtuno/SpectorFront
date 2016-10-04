// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "EnemySpawnController.h"
#include "ActionPhaseController.h"
#include "BaseEnemy.h"
#include "Components/SkeletalMeshComponent.h"

void ABaseEnemy::Wait(float tick)
{
}

void ABaseEnemy::AddObserver(const FScriptDelegate& observer)
{
	notifiEnemyDieEventDispather.AddUnique(observer);
}

void ABaseEnemy::RemoveObserver(UObject* const observer)
{
	notifiEnemyDieEventDispather.RemoveAll(observer);
}

void ABaseEnemy::OnDamage_Implementation(float damage, AController* instigatedBy, AActor* damageCauser)
{
	hp -= damage;
	if (hp <= 0.0f)
	{
		hp = 0.0f;
		OnDeath(instigatedBy, damageCauser);
	}
}

void ABaseEnemy::OnDeath_Implementation(AController * instigatedBy, AActor * damageCauser)
{
	notifiEnemyDieEventDispather.Broadcast(this);
}

void ABaseEnemy::Kill(AController * instigatedBy, AActor * damageCauser)
{
	hp = 0.0f;
	OnDeath(instigatedBy, damageCauser);
}

bool ABaseEnemy::IsDead() const
{
	return hp <= 0.0f;
}
