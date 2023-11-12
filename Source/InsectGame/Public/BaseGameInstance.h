// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Deployables/TowerManager.h"
#include "Enemies/NavigationManager.h"
//#include "Kismet/GameplayStatics.h"

#include "BaseGameInstance.generated.h"

UCLASS()
class INSECTGAME_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UBaseGameInstance();

	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	void SetTowerManager(ATowerManager* TM);
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	ATowerManager* GetTowerManager() const;
	//Navigation
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	void SetNavigationManager(ANavigationManager* TM);
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	ANavigationManager* GetNavigationManager() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ATowerManager* TowerManager;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ANavigationManager* NavigationManager;
};
