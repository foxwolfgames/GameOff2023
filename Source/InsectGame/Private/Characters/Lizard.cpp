//Classes File
#include "Characters/Lizard.h"
#include "Deployables/TowerManager.h"
#include "BaseGameInstance.h"
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

// Sets default values
ALizard::ALizard()
{
	PrimaryActorTick.bCanEverTick = true;

	GameInstance = Cast<UBaseGameInstance>(GetGameInstance());

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 200.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CharacterCamera"));
	ViewCamera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ALizard::BeginPlay()
{
	Super::BeginPlay();
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

void ALizard::RayTrace()
{
	if (!ViewCamera)
		return;
	const FVector CameraLocation = ViewCamera->GetComponentLocation();
	const FRotator CameraRotation = ViewCamera->GetComponentRotation();
	FVector TraceDirection = CameraRotation.Vector();

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	float TraceDistance = 1000.0f;

	FVector TraceEnd = CameraLocation + (TraceDirection * TraceDistance);

	// Perform the ray trace
	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, TraceEnd, ECC_Visibility, TraceParams);

	// Debug visualization in the editor
	if (GEngine)
	{
		
		// Draw a debug line in the editor to visualize the ray (regardless of hit)
		FColor DebugColor = bHit ? FColor::Green : FColor::Red;
		DrawDebugLine(GetWorld(), CameraLocation, TraceEnd, DebugColor, false, -1, 0, 1.0f);
	}

	if (bHit)
	{
		// The ray hit something
		//AActor* HitActor = HitResult.GetActor();

		//Note: initialize RayHitLocation when beginning raytrace, currently 0,0,0
		RayHitLocation = HitResult.ImpactPoint;

		// Do something with the hit result (e.g., spawn a tower or apply logic)
	}
}

void ALizard::PlaceTower()
{
}

void ALizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GEngine)
	{
		GEngine->ClearOnScreenDebugMessages();
	}
	RayTrace();
}

void ALizard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALizard::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALizard::Look);
	}
}

