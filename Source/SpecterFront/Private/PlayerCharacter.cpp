// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "BaseCameraController.h"
#include "PlayerCharacter.h"
#include "MyPlayerController.h"
#include "BaseEnemy.h"
#include "AbstractEnemySpawner.h"

#include "SpecterFrontProjectile.h"
#include "TestMove_PingPong.h"
#include "Animation/AnimInstance.h"
#include "Engine.h"
#include <sstream>
#include "GameFramework/InputSettings.h"

//////////////////////////////////////////////////////////////////////////
// PlayerCharacter

APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	//FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	//FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	//FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);

	aimingSpeed = 60.0f;
	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void APlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	isShootInput = false;
	shootIntervalCount = 0.0f;

	// ビューポートのサイズを格納
	GEngine->GameViewport->GetViewportSize(viewPortSize);

	reticleLocation = viewPortSize / 2.0f;
}

void APlayerCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	std::wostringstream oss(shootIntervalCount);

	if (shootIntervalCount <= 0.0f)
	{
		if (isShootInput)
		{
			OnFire();
			// クールタイムを設定
			shootIntervalCount = shootInterval;
		}
	}
	else
	{
		// クールタイムをカウントダウン
		shootIntervalCount -= deltaTime;
		if (shootIntervalCount <= 0.0f)
		{
			shootIntervalCount = 0.0f;
		}
	}

	Move();
}

void APlayerCharacter::Move_Implementation()
{
}

FVector2D APlayerCharacter::GetReticleLocation() const
{
	return reticleLocation;
}

//////////////////////////////////////////////////////////////////////////
// Input

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &APlayerCharacter::TouchStarted);
	if (EnableTouchscreenMovement(InputComponent) == false)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::OnFirePressed);
		InputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::OnFireReleased);
	}

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APlayerCharacter::MouseHorizontal);
	//InputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APlayerCharacter::MouseVertical);
	//InputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}

void APlayerCharacter::BeginActionPhase(AAbstractEnemySpawner* currentSpawner)
{
	auto cameraControllClass = currentSpawner->GetCameraControllClass();

	if (*cameraControllClass != nullptr)
	{
		currentCameraController = NewObject<UBaseCameraController>(this, *cameraControllClass);
	}

	if (currentCameraController != nullptr)
	{
		currentCameraController->BeginCameraControll(cameraComponent, currentSpawner);
	}
	OnBeginActionPhase(currentSpawner);
}

void APlayerCharacter::TickActionPhase()
{
	if (currentCameraController != nullptr)
	{
		currentCameraController->TickCameraControll(GetWorld()->GetDeltaSeconds());
	}
	OnTickActionPhase();
}

void APlayerCharacter::EndActionPhase()
{
	if (currentCameraController != nullptr)
	{
		currentCameraController->EndCameraControll();
	}
	OnEndActionPhase();
}

void APlayerCharacter::OnFire()
{
	auto controller = Cast<AMyPlayerController>(GetController());
	UWorld* const world = GetWorld();

	if (world != nullptr)
	{
		FVector worldLocation = FVector();
		FVector worldDirection = FVector();
		controller->DeprojectMousePositionToWorld(worldLocation, worldDirection);

		if(controller == nullptr)
			return;

		FHitResult hit;
		FVector start = FVector(worldLocation);
		FVector end = start + worldDirection * 3000.0f;
		ECollisionChannel c = ECollisionChannel::ECC_WorldDynamic;
		FCollisionQueryParams p;
		FCollisionResponseParams rp;
		p.AddIgnoredActor(this);

		bool isHit = world->LineTraceSingleByChannel(hit, start, end, c, p, rp);
		if (isHit && hit.Actor != nullptr)
		{
			//auto o = World->SpawnActor<ASpecterFrontProjectile>(ProjectileClass, hit.ImpactPoint, SpawnRotation);

			if (hit.Actor != this)
			{
				auto component = Cast<UPrimitiveComponent>(hit.Actor->GetComponentByClass(UPrimitiveComponent::StaticClass()));
				

				if (component != nullptr && component->IsSimulatingPhysics())
				{
					GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Cyan, FString(hit.Actor->GetName()));
					FVector to = hit.ImpactPoint;
					FVector from = worldLocation;
					FVector vec = (to - from).GetSafeNormal();
					GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Cyan, hit.Component->GetName());
					hit.Component->SetSimulatePhysics(true);
					hit.Component->AddImpulseAtLocation(vec * 1000000.0f, to);
				}
				else if (hit.Actor->ActorHasTag("Enemy"))
				{
					FVector to = hit.ImpactPoint;
					FVector from = worldLocation;
					FVector vec = (to - from).GetSafeNormal();
					TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
					FDamageEvent DamageEvent(ValidDamageTypeClass);

					auto enemy = Cast<ABaseEnemy, AActor>(hit.Actor);
					enemy->OnDamage(power, GetController(), this);
					onHitDelegate.Broadcast(TScriptInterface<IEnemyInterface>(enemy));
					//if (hit.Component->IsSimulatingPhysics())
					//	hit.Component->AddImpulseAtLocation(vec * 1000000.0f, to);
				}
			}
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

}

void APlayerCharacter::OnFirePressed()
{
	isShootInput = true;
}

void APlayerCharacter::OnFireReleased()
{
	isShootInput = false;
}

void APlayerCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void APlayerCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = false;
}

void APlayerCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
	{
		if (TouchItem.bIsPressed)
		{
			if (GetWorld() != nullptr)
			{
				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
				if (ViewportClient != nullptr)
				{
					FVector MoveDelta = Location - TouchItem.Location;
					FVector2D ScreenSize;
					ViewportClient->GetViewportSize(ScreenSize);
					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.X * BaseTurnRate;
						AddControllerYawInput(Value);
					}
					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.Y * BaseTurnRate;
						AddControllerPitchInput(Value);
					}
					TouchItem.Location = Location;
				}
				TouchItem.Location = Location;
			}
		}
	}
}

void APlayerCharacter::MoveForward(float Value)
{
	//Cast<APlayerController>(Controller)->DeprojectMousePositionToWorld()
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	return;
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::MouseVertical(float rate)
{
	if (GEngine != nullptr && GEngine->GameViewport != nullptr) {
		return;
	}

	// ビューポートのサイズを格納
	GEngine->GameViewport->GetViewportSize(viewPortSize);

	reticleLocation.Y += rate * aimingSpeed * GWorld->GetDeltaSeconds();

	// 範囲制限
	if (reticleLocation.Y > viewPortSize.Y - aimingAreaMargin)
	{
		reticleLocation.Y = viewPortSize.Y - aimingAreaMargin;
	}

	if (reticleLocation.Y < aimingAreaMargin)
	{
		reticleLocation.Y = aimingAreaMargin;
	}
}

void APlayerCharacter::MouseHorizontal(float rate)
{
	if (GEngine != nullptr && GEngine->GameViewport != nullptr) {
		return;
	}
	// ビューポートのサイズを格納
	GEngine->GameViewport->GetViewportSize(viewPortSize);

	reticleLocation.X += rate * aimingSpeed * GWorld->GetDeltaSeconds();

	if (reticleLocation.X > viewPortSize.X - aimingAreaMargin)
	{
		reticleLocation.X = viewPortSize.X - aimingAreaMargin;
	}

	if (reticleLocation.X < aimingAreaMargin)
	{
		reticleLocation.X = aimingAreaMargin;
	}
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	return;
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool APlayerCharacter::EnableTouchscreenMovement(class UInputComponent* InputComponent)
{
	bool bResult = false;
	if (FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		bResult = true;
		InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &APlayerCharacter::BeginTouch);
		InputComponent->BindTouch(EInputEvent::IE_Released, this, &APlayerCharacter::EndTouch);
		InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &APlayerCharacter::TouchUpdate);
	}
	return bResult;
}

void APlayerCharacter::SetReticleLocation(FVector2D location)
{
	if (GEngine->IsValidLowLevel()) {
		if (GEngine->GameViewport == nullptr) {
			return;
		}

		GEngine->GameViewport->GetViewportSize(viewPortSize);
	}

	reticleLocation.X = location.X;
	reticleLocation.Y = location.Y;

	// 範囲制限
	if (reticleLocation.X > viewPortSize.X - aimingAreaMargin)
	{
		reticleLocation.X = viewPortSize.X - aimingAreaMargin;
	}

	if (reticleLocation.X < aimingAreaMargin)
	{
		reticleLocation.X = aimingAreaMargin;
	}

	if (reticleLocation.Y > viewPortSize.Y - aimingAreaMargin)
	{
		reticleLocation.Y = viewPortSize.Y - aimingAreaMargin;
	}

	if (reticleLocation.Y < aimingAreaMargin)
	{
		reticleLocation.Y = aimingAreaMargin;
	}
}

void APlayerCharacter::OnDamage_Implementation(float damage, AController* instigatedBy, AActor* damageCauser)
{

}