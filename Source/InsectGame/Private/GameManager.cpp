// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "BaseGameInstance.h"

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	if (UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance()))
	{
		GameInstance->SetGameManager(this);
	}
	CurrentWave = 0;
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
	CountDown(10);
}

void AGameManager::SpawnWave()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Spawning Wave %d"), CurrentWave));

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

