#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorAttribute.generated.h"


UCLASS( Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INSECTGAME_API UActorAttribute : public UActorComponent
{
	GENERATED_BODY()

public:	
	UActorAttribute();
	UActorAttribute(bool canTick);
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
