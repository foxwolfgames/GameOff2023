// Fill out your copyright notice in the Description page of Project Settings.


#include "Deployables/Tower.h"

// Sets default values
ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;

	AttackRange = 1000.f;
	AttackDamage = 10.f;
	AttackSpeed = 1.f;
	HitPoints = 300.f;
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATower::FireAtTarget(AActor* Target)
{
	if (!Target)
		return;
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

