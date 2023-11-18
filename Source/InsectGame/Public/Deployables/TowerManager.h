// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Deployables/Tower.h"

#include "TowerManager.generated.h"

class ATowerFactory;

UCLASS()
class INSECTGAME_API ATowerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ATowerManager();
	//virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = "Towers")
	TArray<TSubclassOf<ATower>> TowerTypes;
	//Functions
	UFUNCTION()
	ATower* GetTowerByIndex(int32 index);
	UFUNCTION()
	void DeployTower(int32 index, FVector Location, FRotator Rotation);

protected:
	virtual void BeginPlay() override;

private:
	//bool hidden;
	int32 PreviewSize;
	//Cache
	UPROPERTY()
	ATowerFactory* TowerFactory;
	UPROPERTY(EditAnywhere)
	TArray<ATower*> PreviewTowers;
	UPROPERTY()
	TArray<ATower*> TowersList;
};
