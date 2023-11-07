// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "Lizard.generated.h"

class UBaseGameInstance;
class ATowerManager;
//class ATower;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
//class UArrowComponent;

UCLASS()
class INSECTGAME_API ALizard : public ACharacter
{
	GENERATED_BODY()

public:
	ALizard();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* MappingContext;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* EKeyAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LMBAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ESCAction;
	//Functions
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void EKey();
	void LMB();
	void ESC();

private:
	//Values
	bool E_Toggle = false;
	bool bCanPlace = false;
	int32 PreviewTowerIndex = 0;
	//Cache
	UPROPERTY(VisibleAnywhere)
	UBaseGameInstance* GameInstance;
	UPROPERTY(VisibleAnywhere)
	ATowerManager* TowerManager;
	UPROPERTY(VisibleAnywhere)
	APlayerController* PlayerControl;
	UPROPERTY(EditAnywhere, Category = Tower)
	TSubclassOf<AActor> Tower;
	UPROPERTY(EditAnywhere, Category = Raytrace)
	FVector RayHitLocation;
	UPROPERTY(EditAnywhere, Category = Raytrace)
	FRotator RayHitRotation;
	//Components
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
	//UPROPERTY(VisibleAnywhere)
	//ATower* PreviewTowerActor = nullptr;
	//Functions
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	void RayTrace();
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	void PreviewTower(int32 index);
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	void PlaceTower();
};
