// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"


class ATowerManager;

UCLASS()
class INSECTGAME_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UBaseGameInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ATowerManager* TowerManager;
};
