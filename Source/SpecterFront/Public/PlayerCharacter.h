// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyCharacter.h"
#include "DamageListenerInterface.h"
#include "PlayerCharacter.generated.h"

// 攻撃ヒット時のデリゲート
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHitDelegate, AActor*, hitActor, float, damage);


UCLASS()
class SPECTERFRONT_API APlayerCharacter : public AMyCharacter, public IDamageListenerInterface
{
	GENERATED_BODY()

private:

	friend class AMyPlayerController;

	///** Pawn mesh: 1st person view (arms; seen only by self) */
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//	class USkeletalMeshComponent* Mesh1P;

	///** Gun mesh: 1st person view (seen only by self) */
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//	class USkeletalMeshComponent* FP_Gun;

	///** Location on gun mesh where projectiles should spawn. */
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//	class USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//	class UCameraComponent* FirstPersonCameraComponent;
public:
	APlayerCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void Move();

	// レティクル座標を返す
	UFUNCTION(BlueprintCallable, Category = "Character")
		FVector2D GetReticleLocation() const;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ASpecterFrontProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	// IDamageListenerInterfaceの実装
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void OnDamage(float damage, AController* instigatedBy, AActor* damageCauser);

	// アクションフェーズ開始時に呼び出す
	UFUNCTION(BlueprintCallable, Category = "GameFlow")
		void BeginActionPhase(class AAbstractEnemySpawner* currentSpawner);

	// アクションフェーズ開始時に呼び出される
	UFUNCTION(BlueprintImplementableEvent, Category = "GameFlow")
		void OnBeginActionPhase(class AAbstractEnemySpawner* currentSpawner);

	// アクションフェーズ中、マイフレーム呼び出す
	UFUNCTION(BlueprintCallable, Category = "GameFlow")
		void TickActionPhase();

	// アクションフェーズ中、マイフレーム呼び出される
	UFUNCTION(BlueprintImplementableEvent, Category = "GameFlow")
		void OnTickActionPhase();

	// アクションフェーズ終了時に呼び出す
	UFUNCTION(BlueprintCallable, Category = "GameFlow")
		void EndActionPhase();

	// アクションフェーズ終了時に呼び出される
	UFUNCTION(BlueprintImplementableEvent, Category = "GameFlow")
		void OnEndActionPhase();

	// 現在のカメラコントローラを取得
	UFUNCTION(BlueprintCallable, Category = "Player")
		UBaseCameraController* GetCurrentCameraController() { return currentCameraController; }

protected:

	/** Fires a projectile. */
	UFUNCTION(BlueprintNativeEvent, Category = "Player")
		void OnFire();

	void OnFirePressed();
	void OnFireReleased();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	// マウスの垂直移動
	void MouseVertical(float rate);

	// マウスの水平移動
	void MouseHorizontal(float rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false; Location = FVector::ZeroVector; }
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/*
	* Configures input for touchscreen devices if there is a valid touch interface for doing so
	*
	* @param	InputComponent	The input component pointer to bind controls to
	* @returns true if touch controls were enabled.
	*/
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns FirstPersonCameraComponent subobject **/
	//FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	// HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float hp;

	// 攻撃力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float power;

	// 発射間隔(秒)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float shootInterval = 0.2f;

	// 照準速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		float aimingSpeed;

protected:
	UPROPERTY(BlueprintReadWrite, Category = Camera, meta = (BlueprintProtected))
		class UCameraComponent* cameraComponent;

private:
	// 発射可能時間までをカウントダウンする(0.0f以下なら発射可能)
	float shootIntervalCount;

	// 発射入力をTick()で処理するために使用
	bool isShootInput;

	// レティクル座標
	FVector2D reticleLocation;

	// ビューポートからマージン分縮めたエリアをエイミングエリアとする
	const float aimingAreaMargin = 20.0f;

	FVector2D viewPortSize;

	// 現在のカメラコントローラ
	UPROPERTY()
		UBaseCameraController* currentCameraController;

	UPROPERTY()
		class AAbstractEnemySpawner* currentEnemySpawner;

	UPROPERTY(BlueprintAssignable, meta = (AllowPrivateAccess = "true"))
		FOnHitDelegate onHitDelegate;

	void SetReticleLocation(FVector2D location);
};
