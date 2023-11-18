// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

class ABaseEnemy;
class AEnemyFactory;

UCLASS()
class INSECTGAME_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyManager();
	UPROPERTY()
	AEnemyFactory* EnemyFactory;
	//virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = "Enemies")
	TArray<TSubclassOf<ABaseEnemy>> EnemyTypes;

	//Functions
	//ABaseEnemy* GetEnemyByIndex(int32 index);
	UFUNCTION(CallInEditor)
	void DeployEnemy(TSubclassOf<ABaseEnemy> BP, const TArray<AActor*>& TPList, FRotator Rotation);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	int32 EnemyTypeSize;
	UPROPERTY()
	TArray<ABaseEnemy*> EnemiesList;
};
