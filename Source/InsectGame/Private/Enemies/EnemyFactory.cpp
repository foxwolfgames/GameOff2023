// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyFactory.h"
#include "Enemies/BaseEnemy.h"

ABaseEnemy* AEnemyFactory::CreateEnemy(TSubclassOf<ABaseEnemy> EnemyClass, const TArray<AActor*>& TPList, FRotator Rotation)
{
    UWorld* World = GetWorld();
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("In CreateEnemy"));
    if (World && TPList.Num() > 0 && TPList[0])
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Creating Enemy: %s"), *EnemyClass->GetName()));
        }
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        ABaseEnemy* NewEnemy = World->SpawnActor<ABaseEnemy>(EnemyClass, TPList[0]->GetActorLocation(), Rotation, SpawnParams);
        return NewEnemy;
    }
    return nullptr;
}

void AEnemyFactory::BeginPlay()
{
	Super::BeginPlay();
	
}


