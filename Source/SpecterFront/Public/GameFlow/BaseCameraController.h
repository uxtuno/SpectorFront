// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BaseCameraController.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class SPECTERFRONT_API UBaseCameraController : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "CameraController")
		void OnBeginCameraControll(class UCameraComponent* controlCamera, class AAbstractEnemySpawner* currentSpawner);
	virtual void BeginCameraControll(class UCameraComponent* controlCamera, class AAbstractEnemySpawner* currentSpawner);
	UFUNCTION(BlueprintImplementableEvent, Category = "CameraController")
		void OnTickCameraControll(float deltaSeconds);
	virtual void TickCameraControll(float deltaSeconds);
	UFUNCTION(BlueprintImplementableEvent, Category = "CameraController")
		void OnEndCameraControll();
	virtual void EndCameraControll();

	UFUNCTION(BlueprintCallable, Category = "CameraController")
		UCameraComponent* GetControlCamera() const { return controlCamera; }

	UFUNCTION(BlueprintCallable, Category = "CameraController")
		class AAbstractEnemySpawner* GetCurrentSpawner() const { return currentSpawner; }

private:
	UPROPERTY()
		UCameraComponent* controlCamera;

	UPROPERTY()
		class AAbstractEnemySpawner* currentSpawner;
};
