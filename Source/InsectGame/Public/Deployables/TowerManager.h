// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerManager.generated.h"

class ATower;
class ATowerFactory;

UCLASS()
class INSECTGAME_API ATowerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ATowerManager();
	//virtual void Tick(float DeltaTime) override;
	TArray<ATower*> TowersList;
	void DeployTower(TSubclassOf<ATower> TowerClass, FVector Location, FRotator Rotation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ATowerFactory* TowerFactory;

};
