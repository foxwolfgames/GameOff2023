// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyManager.h"
#include "Enemies/EnemyFactory.h"
//#include "Enemies/BaseEnemy.h"
#include "BaseGameInstance.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
	PrimaryActorTick.bCanEverTick = false;
	UE_LOG(LogTemp, Warning, TEXT("Init EnemyManager"));
	EnemyFactory = CreateDefaultSubobject<AEnemyFactory>(TEXT("EnemyFactory"));

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
    if (UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance()))
    {
        GameInstance->SetEnemyManager(this);
    }
    UE_LOG(LogTemp, Warning, TEXT("BeginPlay EnemyManager"));
    if (EnemyFactory)
    {
        EnemyTypeSize = EnemyTypes.Num();
    }
}

//ABaseEnemy* AEnemyManager::GetEnemyByIndex(int32 index)
//{
//	return nullptr;
//}

void AEnemyManager::DeployEnemy(int32 index, TArray<AActor*> TPList, FRotator Rotation)
{
    if (!(index >= 0 && index < EnemyTypeSize))
        return;
    if (EnemyFactory)
    {
        // Create a new tower using the TowerFactory
        ABaseEnemy* NewEnemy = EnemyFactory->CreateEnemy(EnemyTypes[index], TPList, Rotation);

        if (NewEnemy)
        {
            EnemiesList.Add(NewEnemy);
        }
    }
}
