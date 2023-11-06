// Fill out your copyright notice in the Description page of Project Settings.


#include "Deployables/TowerFactory.h"
#include "Deployables/Tower.h"

ATower* ATowerFactory::CreateTower(TSubclassOf<ATower> TowerClass, FVector Location, FRotator Rotation)
{
    UWorld* World = GetWorld();
    if (World)
    {
        ATower* NewTower = World->SpawnActor<ATower>(TowerClass, Location, Rotation);
        return NewTower;
    }
    return nullptr;
}

// Called when the game starts or when spawned
void ATowerFactory::BeginPlay()
{
	Super::BeginPlay();
	
}

