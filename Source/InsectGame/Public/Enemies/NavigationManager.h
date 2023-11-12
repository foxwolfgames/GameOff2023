// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavigationManager.generated.h"

UCLASS()
class INSECTGAME_API ANavigationManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ANavigationManager();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:	

};
