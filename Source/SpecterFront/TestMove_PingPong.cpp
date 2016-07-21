// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "TestMove_PingPong.h"


// Sets default values
ATestMove_PingPong::ATestMove_PingPong()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestMove_PingPong::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestMove_PingPong::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ATestMove_PingPong::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

