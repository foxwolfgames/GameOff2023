// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameManager.h"
#include "Characters/Lizard.h"
#include "Deployables/TowerManager.h"
#include "Deployables/Generator.h"
#include "Enemies/EnemyManager.h"
#include "Enemies/NavigationManager.h"
//#include "Kismet/GameplayStatics.h"

#include "BaseGameInstance.generated.h"

UCLASS()
class INSECTGAME_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UBaseGameInstance();
	//Game
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	void SetGameManager(AGameManager* GM) { GameManager = GM; }
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	AGameManager* GetGameManager() const { return GameManager; }
	//Player
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	void SetPlayerCharacter(ALizard* Player) { PlayerCharacter = Player; }
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	ALizard* GetPlayerCharacter() const { return PlayerCharacter; }
	//Tower
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	void SetTowerManager(ATowerManager* TM) { TowerManager = TM; }
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	ATowerManager* GetTowerManager() const { return TowerManager; }
	//Generator
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	void SetGenerator(AGenerator* Gen) { Generator = Gen; }
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	AGenerator* GetGenerator() const { return Generator; }
	//Enemy
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	void SetEnemyManager(AEnemyManager* EM) { EnemyManager = EM; }
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	AEnemyManager* GetEnemyManager() const { return EnemyManager; }
	//Navigation
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	void SetNavigationManager(ANavigationManager* NM) { NavigationManager = NM; }
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	ANavigationManager* GetNavigationManager() const { return NavigationManager; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AGameManager* GameManager;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ALizard* PlayerCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ATowerManager* TowerManager;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AGenerator* Generator;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AEnemyManager* EnemyManager;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ANavigationManager* NavigationManager;
};
