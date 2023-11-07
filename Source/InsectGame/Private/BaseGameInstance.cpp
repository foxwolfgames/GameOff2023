// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"

UBaseGameInstance::UBaseGameInstance()
{
	TowerManager = CreateDefaultSubobject<UTowerManager>(TEXT("TowerManagerInstance"));
}

UTowerManager* UBaseGameInstance::GetTowerManager() const
{
	return TowerManager;
}
