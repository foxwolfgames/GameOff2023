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
}

void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameManager::StartPrepPhase()
{
}

void AGameManager::StartAttackPhase()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Starting Attack Phase"));
}

void AGameManager::SpawnWave()
{
}

