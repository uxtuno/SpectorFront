// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TargetPoint.h"
#include "BaseEnemy.h"
#include "EnemySpawner.generated.h"

// 敵の生成が終了したことを通知する
DECLARE_DYNAMIC_DELEGATE(FFinishSpawnDelegate);

/**
 * 敵の出現位置を指定するためのオブジェクト
 */
UCLASS(Blueprintable, BlueprintType)
class SPECTERFRONT_API AEnemySpawner : public ATargetPoint
{
	GENERATED_BODY()

public:
	// 生成。ブループリント側でオーバーライドする場合はオーバーライド元も呼ぶこと
	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void BeginSpawn(AActionPhaseController* spawnController);

private: // UPROPERTY
	// スポーンを制御するオブジェクト
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		AActionPhaseController* spawnController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ABaseEnemy> spawnEnemyType;

	// 自身が管理する敵
	UPROPERTY(BlueprintReadOnly, meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		TArray<ABaseEnemy*> spawnedEnemies;

	// スポーン状態
	UPROPERTY(BlueprintReadOnly, meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		bool isSpawing;
public:
	// 現在のスポーナーから制御を移す際に呼び出す
	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void FinishSpawn();

	// 生成した敵が死亡したときに呼び出される
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn", meta = (BlueprintProtected))
		void OnEnemyDie(class ABaseEnemy* enemy);

	// 敵を生成する
	// relativeLocation : 自身を中心とした相対的な位置
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn", meta = (BlueprintProtected))
		void EnemySpawn(const FVector& relativeLocation);

	// 管理中の敵の数
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EnemySpawn")
		int32 GetSpawnedEnemyCount();

protected:
	// 敵の生成開始時に呼び出される。Blueprintでオーバーライドして処理を実装する
	UFUNCTION(BlueprintNativeEvent, Category = "EnemySpawn", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		void OnBeginSpawn();
};
