// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

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
    //Functions
    void FireAtTarget(AActor* Target);
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:	

};
