// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "GameFramework/Character.h"
#include "DamageListenerInterface.h"
#include "EnemyInterface.h"
#include "BaseEnemy.generated.h"

// “G‚ª€–S‚µ‚½‚Æ‚«‚É’Ê’m‚·‚é
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifiEnemyDieDelegate, class TScriptInterface<IEnemyInterface>, enemy);
UCLASS(abstract, Blueprintable, BlueprintType)
class SPECTERFRONT_API ABaseEnemy : public APawn, public IDamageListenerInterface, public IEnemyInterface
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	virtual void Wait(float tick);
	//IEnemyInterface‚ÌÀ‘•
	// €–S‚É’Ê’m‚·‚éæ‚ğ“o˜^
	// €–S‚Éobserver‚ÉŠÜ‚Ü‚ê‚éOnEnemyDie()‚ğŒÄ‚Ño‚·
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
		void AddObserver(UObject* observer);
	virtual void AddObserver_Implementation(UObject* observer) override;

	//IEnemyInterface‚ÌÀ‘•
	// ’Ê’mæ‚ğíœ
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
		void RemoveObserver(UObject* observer);
	virtual void RemoveObserver_Implementation(UObject* observer) override;
public: // UFUNCTION
	
	// HP
	UFUNCTION(BlueprintCallable, Category = "Status")
		FORCEINLINE float GetMaxHp() const { return maxHp; }
	// HP
	UFUNCTION(BlueprintCallable, Category = "Status")
		FORCEINLINE float GetHp() const { return hp; }
	// Score
	UFUNCTION(BlueprintCallable, Category = "Status")
		FORCEINLINE int32 GetScore() const { return score; }
	// UŒ‚—Í
	UFUNCTION(BlueprintCallable, Category = "Status")
		FORCEINLINE float GetPower() const { return power; }

	// €–SÏ‚İ‚©
	UFUNCTION(BlueprintCallable, Category = "Character")
		bool IsDead() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character", meta = (BlueprintProtected))
		void OnDeath(AController* instigatedBy, AActor* damageCauser);

	// IDamageListenerInterface‚ÌÀ‘•
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void OnDamage(float damage, AController* instigatedBy, AActor* damageCauser);

	//IEnemyInterface‚ÌÀ‘•
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void MoveTo();

	//IEnemyInterface‚ÌÀ‘•
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void Appearance();

	// E‚·
	UFUNCTION(BlueprintCallable, Category = "Character")
		void Kill(AController* instigatedBy, AActor* damageCauser);

	// €–S‚É’Ê’m‚·‚é
	UPROPERTY(BlueprintAssignable)
		FNotifiEnemyDieDelegate notifiEnemyDieEventDispather;
private: // UPROPERTY
	// HP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		float hp;
	// Score
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		int32 score;
	// UŒ‚—Í
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		float power;
	// Å‘åHP
	UPROPERTY(BlueprintReadOnly, Category = "Status", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		float maxHp;

	
};
