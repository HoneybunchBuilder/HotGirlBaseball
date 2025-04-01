// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "HGBBPlayerStats.generated.h"

USTRUCT(BlueprintType)
struct FHGBBPlayerStats
{
	GENERATED_BODY()

	float MovementSpeed;
	float SwingPower;
	float ThrowPower;
	float ThrowAccuracy;
	float ErrorRate;
	float ReactionTime;
};