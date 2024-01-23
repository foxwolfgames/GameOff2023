// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/LizardAnimInstance.h"
#include "Characters/Lizard.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void ULizardAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	LizardCharacter = Cast<ALizard>(TryGetPawnOwner());
	if (LizardCharacter)
	{
		LizardCharacterMovement = LizardCharacter->GetCharacterMovement();
	}
}

void ULizardAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (LizardCharacterMovement)
	{
		IsAttacking = LizardCharacter->bIsAttacking;
		GroundSpeed = UKismetMathLibrary::VSizeXY(LizardCharacterMovement->Velocity);
	}
}
