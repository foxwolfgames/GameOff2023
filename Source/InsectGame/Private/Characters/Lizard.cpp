//Classes File
#include "Characters/Lizard.h"
#include "Enemies/BaseEnemy.h"
#include "BaseGameInstance.h"
#include "GameManager.h"
#include "Deployables/TowerManager.h"
//#include "Deployables/Tower.h"
//Other Header Files
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
//Enhanced Input
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
//Components
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
//#include "Components/SkeletalMeshComponent.h"
//#include "Components/CapsuleComponent.h"

ALizard::ALizard()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = SpringArmLength;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CharacterCamera"));
	ViewCamera->SetupAttachment(SpringArm);

	GetCharacterMovement()->MaxWalkSpeed = Big_WalkSpeed;
	GetCharacterMovement()->MaxStepHeight = StepHeight;
}

void ALizard::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->SetPlayerCharacter(this);
		TowerManager = GameInstance->GetTowerManager();
		if (TowerManager)
		{
			UE_LOG(LogTemp, Warning, TEXT("Got TowerManager"));
			MaxTowerIndex = TowerManager->PreviewSize - 1;
		}
			
	}
	PlayerControl = Cast<APlayerController>(GetController());
	if (PlayerControl)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerControl->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void ALizard::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	//Movement
	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void ALizard::Look(const FInputActionValue& Value)
{
	const FVector2D LookingVector = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(LookingVector.X);
		AddControllerPitchInput(-LookingVector.Y);
	}
}

void ALizard::Jump()
{
	Super::Jump();

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Jump"));
}
void ALizard::EKey()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("EKey"));
	E_Toggle = !E_Toggle;
	PreviewTower(PreviewTowerIndex);
}

void ALizard::RKey()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("RKey"));
	if (GameInstance)
	{
		if (GameInstance->GetGameManager())
		{
			GameInstance->GetGameManager()->StartAttackPhase();
		}
	}
}

void ALizard::LMB()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("LMB"));
	if (E_Toggle)
		PlaceTower();
	else
		MeleeAttack();
}

void ALizard::LShift()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("LShift"));
	if (bIsResizing)
		return;
	ResizeProgress = 0;
	bIsResizing = true;
}

void ALizard::ESC()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("ESC"));
}

void ALizard::MouseWheel(const FInputActionValue& Value)
{
	const int8 ScrollVal = (int8)Value.Get<float>();
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Scroll: %d"), ScrollVal));
	int8 PreviousTowerIndex = PreviewTowerIndex;
	PreviewTowerIndex += ScrollVal;
	if (PreviewTowerIndex < 0)
		PreviewTowerIndex = MaxTowerIndex;
	else if (PreviewTowerIndex > MaxTowerIndex)
		PreviewTowerIndex = 0;
	TowerManager->GetTowerByIndex(PreviousTowerIndex)->SetVisibility(false);
	TowerManager->GetTowerByIndex(PreviewTowerIndex)->SetVisibility(true);
}

void ALizard::RayTrace()
{
	if (!ViewCamera)
		return;
	const FVector CameraLocation = ViewCamera->GetComponentLocation();
	const FRotator CameraRotation = ViewCamera->GetComponentRotation();
	FVector TraceDirection = CameraRotation.Vector();

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	TraceParams.TraceTag = FName("FloorTrace");

	float TraceDistance = PlaceObjectDistance * 6;
	FVector TraceEnd = CameraLocation + (TraceDirection * TraceDistance);

	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, TraceEnd, ECC_GameTraceChannel1, TraceParams);

	AActor* HitActor = HitResult.GetActor();
	if (GEngine)
	{
		FColor DebugColor = bHit && (FVector::Dist(HitResult.ImpactPoint, GetActorLocation()) > PlaceObjectDistance) && HitActor->ActorHasTag("Placeable") && FMath::Abs(HitResult.ImpactNormal.Z) >= .9f ? FColor::Green : FColor::Red;
		DrawDebugLine(GetWorld(), CameraLocation, TraceEnd, DebugColor, false, -1, 0, 1.0f);
	}

	if (bHit && (FVector::Dist(HitResult.ImpactPoint, GetActorLocation()) > PlaceObjectDistance) && HitActor->ActorHasTag("Placeable") && FMath::Abs(HitResult.ImpactNormal.Z) >= .9f)
	{
		//Note: initialize RayHitLocation when beginning raytrace, currently 0,0,0
		RayHitLocation = HitResult.ImpactPoint;
		RayHitRotation = FRotator::ZeroRotator;
		if (E_Toggle)
		{
			if (TowerManager)
			{
				if (TowerManager->GetTowerByIndex(PreviewTowerIndex))
				{
					TowerManager->GetTowerByIndex(PreviewTowerIndex)->SetVisibility(true);
					TowerManager->GetTowerByIndex(PreviewTowerIndex)->UpdatePosition(RayHitLocation, RayHitRotation);
					bCanPlace = true;
				}
			}
		}
	}
	else
	{
		bCanPlace = false;
		if (E_Toggle)
			if (TowerManager)
				if (TowerManager->GetTowerByIndex(PreviewTowerIndex))
					TowerManager->GetTowerByIndex(PreviewTowerIndex)->SetVisibility(false);
	}
}

void ALizard::PreviewTower(int32 index)
{
	if (TowerManager)
		if (TowerManager->GetTowerByIndex(index)) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("PreviewTower"));
			E_Toggle ? TowerManager->GetTowerByIndex(index)->SetVisibility(true) : TowerManager->GetTowerByIndex(index)->SetVisibility(false);
		}
}

void ALizard::PlaceTower()
{
	if (bCanPlace && TowerManager)
	{
		if (TowerManager)
		{
			TowerManager->DeployTower(0, RayHitLocation, RayHitRotation);
		}
	}
}

void ALizard::MeleeAttack()
{
	float MeleeDamage = 50.f;

	FCollisionShape MeleeCollisionShape = FCollisionShape::MakeSphere(CurrentAttackRadius);

	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FVector StartTrace = GetActorLocation() + GetActorForwardVector() * CurrentAttackRadius;
	FVector EndTrace = StartTrace + GetActorForwardVector() * MeleeCollisionShape.GetSphereRadius();

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		StartTrace,
		EndTrace,
		FQuat::Identity,
		ECC_Pawn,
		MeleeCollisionShape,
		CollisionParams
	);
	if (GetWorld())
	{
		FVector StartLocation = GetActorLocation();
		DrawDebugSphere(GetWorld(), StartTrace, MeleeCollisionShape.GetSphereRadius(), 12, FColor::Green, false, 0.2f);
	}
	for (const FHitResult& Hit : HitResults)
	{
		ABaseEnemy* EnemyActor = Cast<ABaseEnemy>(Hit.GetActor());
		if (EnemyActor)
		{
			EnemyActor->GetHit(Hit.ImpactPoint);
		}
	}
}

void ALizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RayTrace();
	if (bIsResizing)
		UpdateSize(DeltaTime);
}

void ALizard::UpdateSize(float DeltaTime)
{
	if (!bIsResizing)
		return;
	if (bIsBig)
	{
		ResizeProgress = FMath::Clamp(ResizeProgress + (DeltaTime / .5f), 0.0f, 1.0f);
		GetRootComponent()->SetWorldScale3D(FMath::Lerp(FVector(1.f, 1.f, 1.f), FVector(ShrinkScale, ShrinkScale, ShrinkScale), ResizeProgress));
		SpringArm->TargetArmLength = FMath::Lerp(SpringArmLength, SpringArmLength * ShrinkScale * 2.f, ResizeProgress);
		GetCharacterMovement()->MaxWalkSpeed = FMath::Lerp(Big_WalkSpeed, Small_WalkSpeed, ResizeProgress);
		GetCharacterMovement()->MaxStepHeight = FMath::Lerp(StepHeight, StepHeight * ShrinkScale, ResizeProgress);
		SpringArm->ProbeSize = FMath::Lerp(ProbeSize, ProbeSize * ShrinkScale, ResizeProgress);
		PlaceObjectDistance = FMath::Lerp(MaxPlaceObjectDistance, MaxPlaceObjectDistance * ShrinkScale * 2.f, ResizeProgress);
		CurrentAttackRadius = FMath::Lerp(AttackRadius, AttackRadius * ShrinkScale, ResizeProgress);
		if (ResizeProgress >= 1.f)
		{
			bIsResizing = false;
			bIsBig = false;
		}
	}
	else
	{
		ResizeProgress = FMath::Clamp(ResizeProgress + (DeltaTime / .5f), 0.0f, 1.0f);
		GetRootComponent()->SetWorldScale3D(FMath::Lerp(FVector(ShrinkScale, ShrinkScale, ShrinkScale), FVector(1.f, 1.f, 1.f), ResizeProgress));
		SpringArm->TargetArmLength = FMath::Lerp(SpringArmLength * ShrinkScale * 2.f, SpringArmLength, ResizeProgress);
		GetCharacterMovement()->MaxWalkSpeed = FMath::Lerp(Small_WalkSpeed, Big_WalkSpeed, ResizeProgress);
		GetCharacterMovement()->MaxStepHeight = FMath::Lerp(StepHeight * ShrinkScale, StepHeight, ResizeProgress);
		SpringArm->ProbeSize = FMath::Lerp(ProbeSize * ShrinkScale, ProbeSize, ResizeProgress);
		PlaceObjectDistance = FMath::Lerp(MaxPlaceObjectDistance * ShrinkScale * 2.f, MaxPlaceObjectDistance, ResizeProgress);
		CurrentAttackRadius = FMath::Lerp(AttackRadius * ShrinkScale, AttackRadius, ResizeProgress);
		if (ResizeProgress >= 1.f)
		{
			bIsResizing = false;
			bIsBig = true;
		}
	}
}

void ALizard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALizard::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALizard::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ALizard::Jump);
		EnhancedInputComponent->BindAction(EKeyAction, ETriggerEvent::Started, this, &ALizard::EKey);
		EnhancedInputComponent->BindAction(RKeyAction, ETriggerEvent::Started, this, &ALizard::RKey);
		EnhancedInputComponent->BindAction(LMBAction, ETriggerEvent::Started, this, &ALizard::LMB);
		EnhancedInputComponent->BindAction(LShiftAction, ETriggerEvent::Started, this, &ALizard::LShift);
		EnhancedInputComponent->BindAction(ESCAction, ETriggerEvent::Started, this, &ALizard::ESC);
		EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Started, this, &ALizard::MouseWheel);
	}
}


