// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "BaseCameraController.h"
#include "AbstractEnemySpawner.h"

#include "Camera/CameraComponent.h"

void UBaseCameraController::BeginCameraControll(UCameraComponent* controlCamera, AAbstractEnemySpawner* currentSpawner)
{
	this->controlCamera = controlCamera;
	this->currentSpawner = currentSpawner;
	OnBeginCameraControll(controlCamera, currentSpawner);
}

void UBaseCameraController::TickCameraControll(float deltaSeconds)
{
	OnTickCameraControll(deltaSeconds);
}

void UBaseCameraController::EndCameraControll()
{
	OnEndCameraControll();
}
