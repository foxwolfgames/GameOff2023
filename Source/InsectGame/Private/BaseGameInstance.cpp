// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"

UBaseGameInstance::UBaseGameInstance()
{
}

void UBaseGameInstance::SetTowerManager(ATowerManager* TM)
{
	TowerManager = TM;
}

ATowerManager* UBaseGameInstance::GetTowerManager() const
{
	return TowerManager;
}
void UBaseGameInstance::SetNavigationManager(ANavigationManager* NM)
{
	NavigationManager = NM;
}
ANavigationManager* UBaseGameInstance::GetNavigationManager() const
{
	return NavigationManager;
}
/**/