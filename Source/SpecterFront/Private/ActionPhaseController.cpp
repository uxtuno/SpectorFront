// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "BaseEnemy.h"
#include "ActionPhaseController.h"


// Sets default values
AActionPhaseController::AActionPhaseController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActionPhaseController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActionPhaseController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AActionPhaseController::Finish_Implementation()
{

}
