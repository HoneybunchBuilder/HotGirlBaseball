// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "HGBBCardAbility.generated.h"

/** An ability that a card can activate */
UCLASS()
class HOTGIRLBASEBALL_API UHGBBCardAbility : public UGameplayAbility
{
	GENERATED_BODY()
};

/** An ability that a fielding card can activate */
UCLASS()
class HOTGIRLBASEBALL_API UFieldingAbility : public UGameplayAbility
{
	GENERATED_BODY()
};

/** An ability that a batting card can activate */
UCLASS()
class HOTGIRLBASEBALL_API UBattingAbility : public UGameplayAbility
{
	GENERATED_BODY()
};
