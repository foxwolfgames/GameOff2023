// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/BaseEnemy.h"
#include "BaseGameInstance.h"
#include "Characters/Lizard.h"
#include "Deployables/Generator.h"
#include "Enemies/NavigationManager.h"
//Components
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;/**/

	//GetMesh()->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	AIController = Cast<AAIController>(GetController());
	if (UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance()))
	{
		NavigationManager = GameInstance->GetNavigationManager();
		Generator = GameInstance->GetGenerator();
	}/*
	if (NavigationManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Navigation Manager Set"));
		CurrentTarget = NavigationManager->TargetPointArr1[0];
	}*/
	//AIController->MoveToLocation(FVector(0.f, 0.f, 110.f), 20.f, true, true, true);
}

bool ABaseEnemy::InTargetRange(AActor* Target, double Radius)
{
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	return DistanceToTarget <= Radius;
}

void ABaseEnemy::MeleeAttack()
{
	MeleeCooldown = 1.f;
	float MeleeDamage = 50.f;

	FCollisionShape MeleeCollisionShape = FCollisionShape::MakeSphere(50.f);

	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FVector StartTrace = GetActorLocation() + GetActorForwardVector() * 50.f;
	FVector EndTrace = StartTrace + GetActorForwardVector() * MeleeCollisionShape.GetSphereRadius();

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		StartTrace,
		EndTrace,
		FQuat::Identity,
		ECC_Pawn,
		MeleeCollisionShape,
		CollisionParams
	);
	if (GetWorld())
	{
		FVector StartLocation = GetActorLocation();
		DrawDebugSphere(GetWorld(), StartTrace, MeleeCollisionShape.GetSphereRadius(), 12, FColor::Green, false, 0.1f);
	}
	for (const FHitResult& Hit : HitResults)
	{
		AGenerator* Gen = Cast<AGenerator>(Hit.GetActor());
		if (Gen)
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Hit Gen"));
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 25.f, 12, FColor::Red, false, 0.1f);
		}
	}
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!CurrentTarget && (CurrentLane.Num() > 1))
	{
		CurrentTarget = CurrentLane[CurrentLaneIndex++];
		AIController->MoveToActor(CurrentTarget);
	}
	if (CurrentTarget && AIController)
	{
		if(Generator)
			if (InTargetRange(Generator, 600.f))
			{
				if (MeleeCooldown <= 0)
					MeleeAttack();
				else
					MeleeCooldown -= DeltaTime;
			}
		if (InTargetRange(CurrentTarget, 150.f) && (CurrentLaneIndex < CurrentLane.Num()))
		{
			CurrentTarget = CurrentLane[CurrentLaneIndex++];
			AIController->MoveToActor(CurrentTarget);
		}
	}/**/
	
}

void ABaseEnemy::SetCurrentLane(TArray<AActor*> Lane)
{
	CurrentLane = Lane;
}

void ABaseEnemy::GetHit(const FVector& ImpactPoint)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Hit Enemy"));
	DrawDebugSphere(GetWorld(), ImpactPoint, 25.f, 12, FColor::Red, true);
}

