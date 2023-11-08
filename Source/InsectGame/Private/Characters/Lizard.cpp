//Classes File
#include "Characters/Lizard.h"
#include "BaseGameInstance.h"
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
	SpringArm->TargetArmLength = 200.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CharacterCamera"));
	ViewCamera->SetupAttachment(SpringArm);

}

void ALizard::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		TowerManager = GameInstance->GetTowerManager();
		if(TowerManager)
			UE_LOG(LogTemp, Warning, TEXT("Got TowerManager"));
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
	E_Toggle  = !E_Toggle;
	PreviewTower(PreviewTowerIndex);
}

void ALizard::LMB()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("LMB"));
	PlaceTower();
}

void ALizard::ESC()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("ESC"));
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

	float TraceDistance = 600.0f;
	FVector TraceEnd = CameraLocation + (TraceDirection * TraceDistance);

	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, TraceEnd, ECC_GameTraceChannel1, TraceParams);

	AActor* HitActor = HitResult.GetActor();
	if (GEngine)
	{
		FColor DebugColor = bHit && (FVector::Dist(HitResult.ImpactPoint, GetActorLocation()) > 100.f) && HitActor->ActorHasTag("Placable") ? FColor::Green : FColor::Red;
		DrawDebugLine(GetWorld(), CameraLocation, TraceEnd, DebugColor, false, -1, 0, 1.0f);
	}

	if (bHit && (FVector::Dist(HitResult.ImpactPoint, GetActorLocation()) > 100.f) && HitActor->ActorHasTag("Placable"))
	{
		//Note: initialize RayHitLocation when beginning raytrace, currently 0,0,0
		RayHitLocation = HitResult.ImpactPoint;
		RayHitRotation = FRotator::ZeroRotator;
		if (E_Toggle)
		{
			if (TowerManager)
			{
				TowerManager->GetTowerByIndex(PreviewTowerIndex)->SetVisibility(true);
				TowerManager->GetTowerByIndex(PreviewTowerIndex)->UpdatePosition(RayHitLocation, RayHitRotation);
				bCanPlace = true;
			}
		}
	}
	else
	{
		bCanPlace = false;
		if (E_Toggle)
		{
			if (TowerManager)
			{
				TowerManager->GetTowerByIndex(PreviewTowerIndex)->SetVisibility(false);
			}
		}
	}
}

void ALizard::PreviewTower(int32 index)
{
	if (TowerManager)
	{
		E_Toggle ? TowerManager->GetTowerByIndex(index)->SetVisibility(true) : TowerManager->GetTowerByIndex(index)->SetVisibility(false);
	}
}

void ALizard::PlaceTower()
{
	if (bCanPlace && E_Toggle && TowerManager)
	{
		if (TowerManager)
		{
			TowerManager->DeployTower(0, RayHitLocation, RayHitRotation);
		}
	}
}

void ALizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RayTrace();
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
		EnhancedInputComponent->BindAction(LMBAction, ETriggerEvent::Started, this, &ALizard::LMB);
		EnhancedInputComponent->BindAction(ESCAction, ETriggerEvent::Started, this, &ALizard::ESC);
	}
}


