// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "BaseGameInstance.h"
#include "TimerManager.h"
#include "Enemies/EnemyManager.h"
#include "Enemies/NavigationManager.h"
#include "Components/AudioComponent.h"

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
	PrepPhaseBGMusic = CreateDefaultSubobject<UAudioComponent>(TEXT("PrepBackgroundMusic"));
	DefensePhaseBGMusic = CreateDefaultSubobject<UAudioComponent>(TEXT("DefenseBackgroundMusic"));
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	DefensePhaseBGMusic->Stop();
	if (UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance()))
	{
		GameInstance->SetGameManager(this);
		NavigationManager = GameInstance->GetNavigationManager();
		//if (GEngine && NavigationManager)
		//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("NavigationManager set"));
		EnemyManager = GameInstance->GetEnemyManager();
		//if (GEngine && EnemyManager)
		//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("EnemyManager set"));
	}
	CurrentWave = 0;
	CurrentEnemy = 0;
	WaveList.SetNum(Waves.Num());
	RandomSort();
	StartPrepPhase();
}

void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameManager::StartPrepPhase()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Starting Prep Phase"));
	if (!PrepState)
	{
		DefensePhaseBGMusic->Stop();
		PrepPhaseBGMusic->Play();
	}
	PrepState = true;
}

void AGameManager::StartAttackPhase()
{
	if (LockStartWave || CurrentWave >= Waves.Num())
		return;
	LockStartWave = true;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Starting Attack Phase"));
	if (UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance()))
	{
		NavigationManager = GameInstance->GetNavigationManager();
		EnemyManager = GameInstance->GetEnemyManager();
	}
	CountDown(3);
}

void AGameManager::SpawnWave()
{
	CurrentEnemy = 0;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameManager::SpawnEnemy, 1.f, true, 1.f);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Spawning Wave %d"), CurrentWave));

}

void AGameManager::SpawnEnemy()
{
	if (EnemyManager)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("EnemyManager"));
	if (NavigationManager)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NavigationManager"));
	if (EnemyManager && NavigationManager)
	{
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Spawning Enemy Type %d"), Wave[CurrentWave].GetVal(1, CurrentEnemy)));
		if (WaveList[CurrentWave].GetBP(1, CurrentEnemy))
			EnemyManager->DeployEnemy(WaveList[CurrentWave].GetBP(1, CurrentEnemy), NavigationManager->TargetPointArr1, FRotator::ZeroRotator);
		if (WaveList[CurrentWave].GetBP(2, CurrentEnemy))
			EnemyManager->DeployEnemy(WaveList[CurrentWave].GetBP(2, CurrentEnemy), NavigationManager->TargetPointArr2, FRotator::ZeroRotator);
		if (WaveList[CurrentWave].GetBP(3, CurrentEnemy))
			EnemyManager->DeployEnemy(WaveList[CurrentWave].GetBP(3, CurrentEnemy), NavigationManager->TargetPointArr3, FRotator::ZeroRotator);
		if (WaveList[CurrentWave].GetBP(4, CurrentEnemy))
			EnemyManager->DeployEnemy(WaveList[CurrentWave].GetBP(4, CurrentEnemy), NavigationManager->TargetPointArr4, FRotator::ZeroRotator);
		//EnemyManager->DeployEnemy(Waves[CurrentWave].EnemyBP, NavigationManager->TargetPointArr1, FRotator::ZeroRotator);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Current Enemy %d"), CurrentEnemy));
	CurrentEnemy++;
	if (CurrentEnemy < WaveList[CurrentWave].Lane1.Num() + 1)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameManager::SpawnEnemy, 1.0f, false);
	}
	else
	{
		LockStartWave = false;
		CurrentWave++;
	}


}

void AGameManager::RandomSort()
{
	//For each wave:
	for (int8 waveIndex = 0; waveIndex < Waves.Num(); waveIndex++)
	{
		TArray<int32> TempArr;
		//TempArr.SetNum(Waves[waveIndex].EnemyArray.Num());
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("EnemyArrayNum %d"), Waves[waveIndex].EnemyArray.Num()));
		for (int8 i = 0; i < Waves[waveIndex].EnemyArray.Num(); i++)
		{
			TempArr.Add(Waves[waveIndex].EnemyArray[i].Amount);
		}
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("TempArrNum %d"), TempArr.Num()));
		while (!TempArr.IsEmpty())
		{
			int32 ranIndex = FMath::RandRange(0, TempArr.Num() - 1);
			WaveList[waveIndex].AddBP(laneIndex++, Waves[waveIndex].EnemyArray[ranIndex].EnemyBP);
			if (laneIndex > 4)
				laneIndex = 1;
			if (TempArr[ranIndex] > 1)
				TempArr[ranIndex]--;
			else
				TempArr.RemoveAt(ranIndex);
		}
	}
}

void AGameManager::DisplayCount()
{
	if (GEngine)
	{
		FString CountdownString = FString::Printf(TEXT("Countdown: %d"), TimeCount);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, CountdownString);
	}
}

void AGameManager::CountDown(int32 start)
{
	TimeCount = start;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameManager::CountDownTick, 1.f, true, 1.f);
}

void AGameManager::CountDownTick()
{
	DisplayCount();
	TimeCount--;
	if (TimeCount < 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		if (PrepState)
		{
			PrepPhaseBGMusic->Stop();
			DefensePhaseBGMusic->Play();
		}
		PrepState = false;
		SpawnWave();
	}
}

