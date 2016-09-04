// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "PlayerCharacter.h"
#include "BaseEnemy.h"

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
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void APlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); //Attach gun mesh component to Skeleton, doing it here because the skelton is not yet created in the constructor

	isShootInput = false;
	shootIntervalCount = 0.0f;

	reticleLocation = FVector2D(0.5f, 0.5f);
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
	InputComponent->BindAxis("Turn", this, &APlayerCharacter::MouseVertical);
	//InputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APlayerCharacter::MouseHorizontal);
	//InputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}

void APlayerCharacter::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();

		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			FHitResult hit;
			FVector start = FVector(Cast<UCameraComponent>(GetComponentByClass(UCameraComponent::StaticClass()))->GetComponentLocation());
			FVector end = start + Cast<UCameraComponent>(GetComponentByClass(UCameraComponent::StaticClass()))->GetForwardVector() * 3000.0f;
			ECollisionChannel c = ECollisionChannel::ECC_WorldStatic;
			FCollisionQueryParams p;
			FCollisionResponseParams rp;
			p.AddIgnoredActor(this);

			bool isHit = World->LineTraceSingleByChannel(hit, start, end, c, p, rp);
			if (isHit)
			{
				//auto o = World->SpawnActor<ASpecterFrontProjectile>(ProjectileClass, hit.ImpactPoint, SpawnRotation);

				auto component = Cast<UPrimitiveComponent>(hit.Actor->GetComponentByClass(UPrimitiveComponent::StaticClass()));
				if ((hit.Actor != NULL) && (hit.Actor != this) && component->IsSimulatingPhysics())
				{
					GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Cyan, FString(hit.Actor->GetName()));
					FVector to = hit.ImpactPoint;
					FVector from = FP_Gun->GetComponentLocation();
					FVector vec = (to - from).GetSafeNormal();
					GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Cyan, hit.Component->GetName());
					hit.Component->SetSimulatePhysics(true);
					hit.Component->AddImpulseAtLocation(vec * 1000000.0f, to);
				}
				else if (hit.Actor->ActorHasTag("Enemy"))
				{
					FVector to = hit.ImpactPoint;
					FVector from = FP_Gun->GetComponentLocation();
					FVector vec = (to - from).GetSafeNormal();
					TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
					FDamageEvent DamageEvent(ValidDamageTypeClass);

					Cast<ABaseEnemy, AActor>(hit.Actor)->OnDamage(power, GetController(), this);
					if (hit.Component->IsSimulatingPhysics())
						hit.Component->AddImpulseAtLocation(vec * 1000000.0f, to);
				}
			}
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
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
	reticleLocation.Y += rate;
}

void APlayerCharacter::MouseHorizontal(float rate)
{
	reticleLocation.X += rate;
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
