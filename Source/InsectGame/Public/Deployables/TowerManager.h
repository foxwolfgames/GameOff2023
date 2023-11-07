// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TowerManager.generated.h"

class ATower;
class ATowerFactory;

UCLASS()
class INSECTGAME_API UTowerManager : public UObject
{
	GENERATED_BODY()
	
public:	
	UTowerManager();
	//virtual void Tick(float DeltaTime) override;
	TArray<ATower*> TowersList;
	void DeployTower(TSubclassOf<ATower> TowerClass, FVector Location, FRotator Rotation);

protected:

private:
	UPROPERTY()
	ATowerFactory* TowerFactory;

};
