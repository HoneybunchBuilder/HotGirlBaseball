// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "MuCO/CustomizableObjectInstance.h"
#include "HGBBPlayer.generated.h"

USTRUCT(BlueprintType)
struct FHGBBPlayerStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MovementSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SwingPower;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ThrowPower;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ThrowAccuracy;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ErrorRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ReactionTime;
};

UCLASS(Abstract, Blueprintable, BlueprintType)
class UHGBBPlayer : public UObject
{
	GENERATED_BODY()

public:
	UHGBBPlayer() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCustomizableObjectInstance> CharacterInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FHGBBPlayerStats Stats = {};
};

USTRUCT(BlueprintType)
struct FHGBBPlayerRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHGBBPlayer> Player;
};
