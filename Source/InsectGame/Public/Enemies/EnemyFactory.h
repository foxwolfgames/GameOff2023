// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFactory.generated.h"

class ABaseEnemy;

UCLASS()
class INSECTGAME_API AEnemyFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	//AEnemyFactory();
	//virtual void Tick(float DeltaTime) override;
	UFUNCTION(CallInEditor)
	ABaseEnemy* CreateEnemy(TSubclassOf<ABaseEnemy> EnemyClass, const TArray<AActor*>& TPList, FRotator Rotation);

protected:
	virtual void BeginPlay() override;

private:

};
