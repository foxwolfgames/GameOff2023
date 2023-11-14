// Fill out your copyright notice in the Description page of Project Settings.


#include "Deployables/TowerManager.h"
#include "Deployables/TowerFactory.h"
#include "BaseGameInstance.h"

ATowerManager::ATowerManager()
{
    PrimaryActorTick.bCanEverTick = false;
    UE_LOG(LogTemp, Warning, TEXT("Init TowerManager"));
    TowerFactory = CreateDefaultSubobject<ATowerFactory>(TEXT("TowerFactory"));
}

void ATowerManager::BeginPlay()
{
    Super::BeginPlay();

    if (UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance()))
    {
        GameInstance->SetTowerManager(this);
    }
    UE_LOG(LogTemp, Warning, TEXT("BeginPlay TowerManager"));
    if (TowerFactory)
    {
        PreviewTowers.Empty(TowerTypes.Num());

        for (TSubclassOf<ATower> TowerClass : TowerTypes)
        {
            // Create a preview tower for each tower type
            ATower* PreviewTower = TowerFactory->CreateTower(TowerClass, FVector::ZeroVector, FRotator::ZeroRotator);

            if (PreviewTower)
            {

                // Add the preview tower to the PreviewTowers array
                PreviewTower->ToggleTower(false);
                PreviewTowers.Add(PreviewTower);
                UE_LOG(LogTemp, Warning, TEXT("Add PreviewTower"));
            }
        }
        PreviewSize = PreviewTowers.Num();
    }
}

ATower* ATowerManager::GetTowerByIndex(int32 index)
{
    if(index >= 0 && index < PreviewSize)
        return PreviewTowers[index];
    return nullptr;
}

void ATowerManager::DeployTower(int32 index, FVector Location, FRotator Rotation)
{
    if (!(index >= 0 && index < PreviewSize))
        return;
    if (TowerFactory)
    {
        // Create a new tower using the TowerFactory
        ATower* NewTower = TowerFactory->CreateTower(TowerTypes[index], Location, Rotation);

        if (NewTower)
        {
            TowersList.Add(NewTower);
        }
    }
}
