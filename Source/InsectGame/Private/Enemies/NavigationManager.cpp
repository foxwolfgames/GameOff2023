// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/NavigationManager.h"
#include "BaseGameInstance.h"

// Sets default values
ANavigationManager::ANavigationManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ANavigationManager::BeginPlay()
{
	Super::BeginPlay();

    if (UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance()))
    {
        GameInstance->SetNavigationManager(this);
    }
}

// Called every frame
void ANavigationManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

