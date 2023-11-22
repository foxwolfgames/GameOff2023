#include "Components/ActorAttribute.h"

// Sets default values for this component's properties
UActorAttribute::UActorAttribute()
{
	PrimaryComponentTick.bCanEverTick = false;
}


UActorAttribute::UActorAttribute(bool canTick)
{
	PrimaryComponentTick.bCanEverTick = canTick;
}


// Called when the game starts
void UActorAttribute::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UActorAttribute::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

