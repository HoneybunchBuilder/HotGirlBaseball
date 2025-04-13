// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HGBBCardAbility.h"
#include "HGBBCard.generated.h"

/** The collection of modifiers that can apply to a card */
USTRUCT(BlueprintType)
struct HOTGIRLBASEBALL_API FHGBBCardMods
{
	GENERATED_BODY()
};

/** 
	The base of an individual, unique card in a player's batting or fielding deck

	Don't extend this directly
*/
UCLASS(Abstract, BlueprintType)
class HOTGIRLBASEBALL_API UHGBBCard : public UObject
{
	GENERATED_BODY()

public:
	UHGBBCard() = default;

	/** The user-facing name of the card */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText DisplayName;

	/** The user-facing detail text on the card */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText DetailText;

	/** The primary backing image of the card */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> CardImage;

	/** A detail icon displayed on the card */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(BlueprintReadWrite)
	FHGBBCardMods Mods;
};

/** 
	The base of an individual, unique batting card in a player's deck

	Extend this to make a specific type of card
*/
UCLASS(Abstract, BlueprintType, Blueprintable)
class HOTGIRLBASEBALL_API UBattingCard : public UHGBBCard
{
	GENERATED_BODY()

public:
	UBattingCard() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBattingAbility> Ability;
};

/**
	The base of an individual, unique fielding card in a player's deck

	Extend this to make a specific type of card
*/
UCLASS(Abstract, BlueprintType, Blueprintable)
class HOTGIRLBASEBALL_API UFieldingCard : public UHGBBCard
{
	GENERATED_BODY()

public:
	UFieldingCard() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UFieldingAbility> Ability;
};
