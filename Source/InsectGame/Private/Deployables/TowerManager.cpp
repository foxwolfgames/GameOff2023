// Fill out your copyright notice in the Description page of Project Settings.


#include "Deployables/TowerManager.h"
#include "Deployables/Tower.h"
#include "Deployables/TowerFactory.h"

ATowerManager::ATowerManager()
{
    PrimaryActorTick.bCanEverTick = false;

    TowerFactory = CreateDefaultSubobject<ATowerFactory>(TEXT("TowerFactory"));
}

void ATowerManager::DeployTower(TSubclassOf<ATower> TowerClass, FVector Location, FRotator Rotation)
{
    if (TowerFactory)
    {
        // Create a new tower using the TowerFactory
        ATower* NewTower = TowerFactory->CreateTower(TowerClass, Location, Rotation);

        if (NewTower)
        {
            TowersList.Add(NewTower);
        }
    }
}

// Called when the game starts or when spawned
void ATowerManager::BeginPlay()
{
	Super::BeginPlay();
	
}

