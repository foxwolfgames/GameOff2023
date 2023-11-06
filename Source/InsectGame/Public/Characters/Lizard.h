// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "Lizard.generated.h"

class UBaseGameInstance;
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

protected:
	UPROPERTY(VisibleAnywhere)
	UBaseGameInstance* GameInstance;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* MappingContext;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;
	//Functions
	virtual void BeginPlay() override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

private:
	UPROPERTY(VisibleAnywhere)
	APlayerController* PlayerControl;
	UPROPERTY(EditAnywhere, Category = Tower)
	TSubclassOf<AActor> Tower;
	UPROPERTY(EditAnywhere, Category = Raytrace)
	FVector RayHitLocation;
	//Components
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
	//Functions
	void RayTrace();
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Functions")
	void PlaceTower();
};
