// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

class AEnemyManager;
class ANavigationManager;

USTRUCT()
struct INSECTGAME_API FWave
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<int32> Lane1 = { 0, 0, 0 };
	UPROPERTY()
	TArray<int32> Lane2 = { 0 };
	UPROPERTY()
	TArray<int32> Lane3 = { 0 };
	UPROPERTY()
	TArray<int32> Lane4 = { 0 };

	int32 GetVal(int8 lane, int32 index)
	{
		switch (lane)
		{
		case 1:
			return GetValFromLane(Lane1, index);
		case 2:
			return GetValFromLane(Lane2, index);
		case 3:
			return GetValFromLane(Lane3, index);
		case 4:
			return GetValFromLane(Lane4, index);
		default:
			return -1;
		}
	}
private:
	int32 GetValFromLane(const TArray<int32>& Lane, int32 index)
	{
		if (index >= 0 && index < Lane.Num())
			return Lane[index];
		return -1;
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

protected:
	virtual void BeginPlay() override;

private:
	//For some reason, EditAnywhere is necessary for EnemyManager or else it doesn't get set...
	UPROPERTY(EditAnywhere)
	ANavigationManager* NavigationManager;
	UPROPERTY(EditAnywhere)
	AEnemyManager* EnemyManager;
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
	UPROPERTY()
	TArray<FWave> Wave;
	//Functions
	UFUNCTION()
	void SpawnWave();
	UFUNCTION()
	void SpawnEnemy();
	UFUNCTION()
	void CountDown(int32 start);
	UFUNCTION()
	void DisplayCount();
	UFUNCTION()
	void CountDownTick();
};
