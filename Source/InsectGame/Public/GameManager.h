// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemies/BaseEnemy.h"

#include "GameManager.generated.h"

class AEnemyManager;
class ANavigationManager;

USTRUCT()
struct INSECTGAME_API FEnemy
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseEnemy> EnemyBP;
	UPROPERTY(EditAnywhere)
	int32 Amount = 0;
};
USTRUCT()
struct INSECTGAME_API FEnemies
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TArray<FEnemy> EnemyArray;
};

USTRUCT()
struct INSECTGAME_API FWave
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABaseEnemy>> Lane1;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABaseEnemy>> Lane2;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABaseEnemy>> Lane3;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABaseEnemy>> Lane4;
	void AddBP(int8 lane, TSubclassOf<ABaseEnemy> BP)
	{
		switch (lane)
		{
		case 1:
			Lane1.Add(BP);
			return;
		case 2:
			Lane2.Add(BP);
			return;
		case 3:
			Lane3.Add(BP);
			return;
		case 4:
			Lane4.Add(BP);
			return;
		}
	}
	TSubclassOf<ABaseEnemy> GetBP(int8 lane, int32 index)
	{
		switch (lane)
		{
		case 1:
			return GetBPFromLane(Lane1, index);
		case 2:
			return GetBPFromLane(Lane2, index);
		case 3:
			return GetBPFromLane(Lane3, index);
		case 4:
			return GetBPFromLane(Lane4, index);
		default:
			return nullptr;
		}
	}
private:
	TSubclassOf<ABaseEnemy> GetBPFromLane(const TArray<TSubclassOf<ABaseEnemy>>& Lane, int32 index)
	{
		if (index >= 0 && index < Lane.Num())
			return Lane[index];
		return nullptr;
	}
};

UCLASS()
class INSECTGAME_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void StartPrepPhase();
	UFUNCTION()
	void StartAttackPhase();

	UPROPERTY(EditAnywhere, Category = "Waves List")
	TArray<FEnemies> Waves;

protected:
	virtual void BeginPlay() override;

private:
	//For some reason, EditAnywhere is necessary for EnemyManager or else it doesn't get set...
	UPROPERTY(EditAnywhere)
	ANavigationManager* NavigationManager;
	UPROPERTY(EditAnywhere)
	AEnemyManager* EnemyManager;
	int8 laneIndex = 1;
	//UPROPERTY(EditAnywhere, Category = "Enemies")
	//TArray<int32> EnemiesCount;
	UPROPERTY()
	int32 CurrentWave;
	UPROPERTY()
	int32 CurrentEnemy;
	UPROPERTY()
	FTimerHandle TimerHandle;
	UPROPERTY()
	int32 TimeCount;
	UPROPERTY(VisibleAnywhere, Category = "Waves List")
	TArray<FWave> WaveList;
	//Functions
	UFUNCTION()
	void SpawnWave();
	UFUNCTION()
	void SpawnEnemy();
	UFUNCTION()
	void RandomSort();
	UFUNCTION()
	void CountDown(int32 start);
	UFUNCTION()
	void DisplayCount();
	UFUNCTION()
	void CountDownTick();
};
