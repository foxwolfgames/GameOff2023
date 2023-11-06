// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "Deployables/TowerManager.h"
//#include "Kismet/GameplayStatics.h"

UBaseGameInstance::UBaseGameInstance()
{
	TowerManager = NewObject<ATowerManager>();
}
