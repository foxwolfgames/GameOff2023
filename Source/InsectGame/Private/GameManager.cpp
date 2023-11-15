// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "BaseGameInstance.h"
#include "TimerManager.h"
#include "Enemies/EnemyManager.h"
#include "Enemies/NavigationManager.h"

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
	Wave.SetNum(10);
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	if (UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance()))
	{
		GameInstance->SetGameManager(this);
		NavigationManager = GameInstance->GetNavigationManager();
		if (GEngine && NavigationManager)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("NavigationManager set"));
		EnemyManager = GameInstance->GetEnemyManager();
		if (GEngine && EnemyManager)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("EnemyManager set"));
	}
	CurrentWave = 0;
	CurrentEnemy = 0;
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
}

void AGameManager::StartAttackPhase()
{
	if (EnemiesCount.Num() < 1)
		return;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Starting Attack Phase"));
	CountDown(3);
}

void AGameManager::SpawnWave()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Spawning Wave %d"), CurrentWave));

	CurrentEnemy = 0;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameManager::SpawnEnemy, 1.f, true, 1.f);
}

void AGameManager::SpawnEnemy()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("In SpawnEnemy"));
	if (EnemyManager && NavigationManager)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Spawning Enemy Type %d"), Wave[CurrentWave].GetVal(1, CurrentEnemy)));
		//EnemyManager->DeployEnemy(Wave[CurrentWave].GetVal(1, CurrentEnemy), NavigationManager->TargetPointArr1, FRotator::ZeroRotator);
		EnemyManager->DeployEnemy(0, NavigationManager->TargetPointArr1, FRotator::ZeroRotator);
	}
	CurrentEnemy++;
	if (CurrentEnemy < Wave[CurrentWave].Lane1.Num())
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameManager::SpawnEnemy, 1.0f, false);
	}

}

void AGameManager::CountDown(int32 start)
{
	TimeCount = start;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameManager::CountDownTick, 1.f, true, 1.f);
}

void AGameManager::DisplayCount()
{
	if (GEngine)
	{
		FString CountdownString = FString::Printf(TEXT("Countdown: %d"), TimeCount);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, CountdownString);
	}
}

void AGameManager::CountDownTick()
{
	DisplayCount();
	TimeCount--;
	if (TimeCount < 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		SpawnWave();
	}
}

