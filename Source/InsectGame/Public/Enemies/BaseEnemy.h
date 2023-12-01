// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"

#include "BaseEnemy.generated.h"

class AAIController;
class ANavigationManager;

UCLASS()
class INSECTGAME_API ABaseEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	ABaseEnemy();
	virtual void Tick(float DeltaTime) override;
	void SetCurrentLane(TArray<AActor*> Lane);
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetHit(const FVector& ImpactPoint) override;

protected:
	virtual void BeginPlay() override;

private:
	//Cache
	UPROPERTY(EditAnywhere);
	AAIController* AIController;
	UPROPERTY(VisibleAnywhere)
	ANavigationManager* NavigationManager;
	UPROPERTY()
	TArray<AActor*> CurrentLane;
	int8 CurrentLaneIndex = 1;
	float PatrolRadius = 200.f;
	UPROPERTY()
	AActor* CurrentTarget;/**/
	//Functions
	UFUNCTION()
	bool InTargetRange(AActor* Target, double Radius);
};
