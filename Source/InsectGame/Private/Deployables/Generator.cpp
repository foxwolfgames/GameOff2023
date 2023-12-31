// Fill out your copyright notice in the Description page of Project Settings.


#include "Deployables/Generator.h"
#include "BaseGameInstance.h"

// Sets default values
AGenerator::AGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGenerator::BeginPlay()
{
	Super::BeginPlay();
    if (UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance()))
    {
        GameInstance->SetGenerator(this);
    }
}

// Called every frame
void AGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

