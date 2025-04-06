// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HGBBCardAbility.h"
#include "HGBBCard.generated.h"

/** The styling elements of a card */
USTRUCT(BlueprintType)
struct HOTGIRLBASEBALL_API FHGBBCardStyle
{
	GENERATED_BODY()

	/** The user-facing name of the card */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	/** The user-facing detail text on the card */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DetailText;

	/** The primary backing image of the card */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> CardImage;

	/** A detail icon displayed on the card */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon;
};

/** The collection of modifiers that can apply to a card */
USTRUCT(BlueprintType)
struct HOTGIRLBASEBALL_API FHGBBCardMods
{
	GENERATED_BODY()
};

/** An individual, unique card in a player's batting or fielding deck */
UCLASS(BlueprintType)
class HOTGIRLBASEBALL_API UHGBBCard : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FHGBBCardStyle Style;

	UPROPERTY(BlueprintReadWrite)
	FHGBBCardMods Mods;
};

/** An individual, unique batting card in a player's deck */
UCLASS(BlueprintType, Blueprintable)
class HOTGIRLBASEBALL_API UBattingCard : public UHGBBCard
{
	GENERATED_BODY()

public:
	UBattingCard();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBattingAbility> Ability;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBattingAbility> AbilityPtr;
};

/** An individual, unique fielding card in a player's deck */
UCLASS(BlueprintType, Blueprintable)
class HOTGIRLBASEBALL_API UFieldingCard : public UHGBBCard
{
	GENERATED_BODY()

public:
	UFieldingCard();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFieldingAbility> Ability;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UFieldingAbility> AbilityPtr;
};