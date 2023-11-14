// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyFactory.h"
#include "Enemies/BaseEnemy.h"

ABaseEnemy* AEnemyFactory::CreateEnemy(TSubclassOf<ABaseEnemy> TowerClass, TArray<AActor*> TPList, FRotator Rotation)
{
	return nullptr;
}

void AEnemyFactory::BeginPlay()
{
	Super::BeginPlay();
	
}


