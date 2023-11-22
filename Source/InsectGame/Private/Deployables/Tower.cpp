// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemies/BaseEnemy.h"
#include "Deployables/Tower.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = SkeletalMeshComponent;

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	CollisionCapsule->SetupAttachment(GetRootComponent());

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

void ATower::UpdatePosition(FVector Location, FRotator Rotation)
{
	SetActorLocation(Location);
	SetActorRotation(Rotation);
}

void ATower::SetVisibility(bool b)
{
	SetActorHiddenInGame(!b);
}

void ATower::ToggleTower(bool b)
{
	SetActorHiddenInGame(!b);
	SetActorEnableCollision(b);
	SetActorTickEnabled(b);
}

//past parameter: AActor* Target
void ATower::DetectEnemy()
{
	TArray<ABaseEnemy*> EnemiesInRange;

	for (ABaseEnemy* Enemy : EnemiesInRange)
	{
		FireProjectiles(Enemy);
	}
}

void ATower::FireProjectiles(ABaseEnemy* TargetEnemy)
{

}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

