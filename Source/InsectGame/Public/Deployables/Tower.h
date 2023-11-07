// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

class UCapsuleComponent;

UCLASS()
class INSECTGAME_API ATower : public AActor
{
	GENERATED_BODY()
	
public:	
	ATower();
    //Properties
    UPROPERTY(EditAnywhere, Category = "Tower")
    float AttackRange;
    UPROPERTY(EditAnywhere, Category = "Tower")
    float AttackDamage;
    UPROPERTY(EditAnywhere, Category = "Tower")
    float AttackSpeed;
    UPROPERTY(EditAnywhere, Category = "Tower")
    float HitPoints;
    //Functions - virtual
    virtual void ToggleTower(bool b);
    virtual void FireAtTarget(AActor* Target);
	virtual void Tick(float DeltaTime) override;
    //Functions
    void UpdatePosition(FVector Location, FRotator Rotation);
    void SetVisibility(bool b);

protected:
	virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere)
    UCapsuleComponent* CollisionCapsule;
	UPROPERTY(VisibleAnywhere)
    USkeletalMeshComponent* SkeletalMeshComponent;
};
