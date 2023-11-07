// Fill out your copyright notice in the Description page of Project Settings.


#include "Deployables/TowerManager.h"
#include "Deployables/Tower.h"
#include "Deployables/TowerFactory.h"

UTowerManager::UTowerManager()
{

    TowerFactory = CreateDefaultSubobject<ATowerFactory>(TEXT("TowerFactory"));
}

void UTowerManager::DeployTower(TSubclassOf<ATower> TowerClass, FVector Location, FRotator Rotation)
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


