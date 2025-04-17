// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HGBBTypes.h"
#include "HGBBBatterBox.generated.h"

/**
	An actor that marks up where a batter should be placed when at bat
*/
UCLASS(BlueprintType, Blueprintable)
class HOTGIRLBASEBALL_API AHGBBBatterBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AHGBBBatterBox();

	/** Gets whether this batters box is for left handed or right handed batters */
	UFUNCTION(BlueprintCallable)
	EHandedness GetHandedness();

private:
	/** Whether this batters box is for left handed or right handed batters */
	UPROPERTY(EditInstanceOnly)
	EHandedness Handedness;
};
