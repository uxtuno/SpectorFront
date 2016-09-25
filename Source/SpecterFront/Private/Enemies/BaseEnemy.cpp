// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "EnemySpawnController.h"
#include "BaseEnemy.h"

void ABaseEnemy::Wait(float tick)
{
}

void ABaseEnemy::SetSpawnController(AEnemySpawnController* spawnController)
{
	this->spawnController = spawnController;
}

void ABaseEnemy::OnDamage_Implementation(float damage, AController* instigatedBy, AActor* damageCauser)
{
	hp -= damage;
	if (hp < 0.0f)
	{
		hp = 0.0f;
		OnDeath(instigatedBy, damageCauser);
		spawnController->OnEnemyDie(this);
	}
}

bool ABaseEnemy::IsDead() const
{
	return hp <= 0.0f;
}
