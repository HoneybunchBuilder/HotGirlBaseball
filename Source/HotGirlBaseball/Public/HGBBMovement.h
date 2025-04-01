// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HGBBMovement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOTGIRLBASEBALL_API UHGBBMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHGBBMovement();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
