// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class INSECTGAME_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void StartPrepPhase();
	UFUNCTION()
	void StartAttackPhase();
	UFUNCTION()
	void SpawnWave();

protected:
	virtual void BeginPlay() override;

private:	

};
