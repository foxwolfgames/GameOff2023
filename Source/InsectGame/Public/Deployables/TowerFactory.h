// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerFactory.generated.h"

class ATower;

UCLASS()
class INSECTGAME_API ATowerFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	//ATowerFactory();
	//virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	ATower* CreateTower(TSubclassOf<ATower> TowerClass, FVector Location, FRotator Rotation);

protected:
	virtual void BeginPlay() override;

private:	
};
