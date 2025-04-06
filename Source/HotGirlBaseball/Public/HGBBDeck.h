// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "HGBBCard.h"
#include "HGBBDeck.generated.h"

/** A structure containing the basics of a Deck object */
USTRUCT(BlueprintType)
struct HOTGIRLBASEBALL_API FHGBBDeckDesc : public FTableRowBase
{
	GENERATED_BODY()

	/** The user-facing name of this deck */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText DisplayName;

	/** The user-facing icon that represents this deck in the UI */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UTexture2D> Icon;
};

/** A structure describing a batting deck */
USTRUCT(BlueprintType)
struct HOTGIRLBASEBALL_API FBattingDeckDesc : public FHGBBDeckDesc
{
	GENERATED_BODY()

	/**  A map describing how many of each type of batting card belongs in this deck */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<TSubclassOf<UBattingCard>, int32> CardTypes;
};

/** A structure describing a fielding deck */
USTRUCT(BlueprintType)
struct HOTGIRLBASEBALL_API FFieldingDeckDesc : public FHGBBDeckDesc
{
	GENERATED_BODY()

	/** A map describing how many of each type of fielding card belongs in this deck */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<TSubclassOf<UFieldingCard>, int32> CardTypes;
};

/** A Collection of cards along with some metadata */
UCLASS(BlueprintType)
class HOTGIRLBASEBALL_API UHGBBDeck : public UObject
{
	GENERATED_BODY()

public:
	UHGBBDeck() = default;
	UHGBBDeck(const FHGBBDeckDesc& Descriptor);

	/** The user-facing name of this deck */
	UPROPERTY(BlueprintReadOnly)
	FText DisplayName;

	/** The user-facing icon that represents this deck in the UI */
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon;
};

/** A Collection of batting cards */
UCLASS(BlueprintType, Blueprintable)
class HOTGIRLBASEBALL_API UBattingDeck : public UHGBBDeck
{
	GENERATED_BODY()

public:
	UBattingDeck() = default;
	UBattingDeck(const FBattingDeckDesc& Descriptor);

	/** The collection of cards spawned and owned by this deck */
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UBattingCard>> Cards;
};

/** A Collection of fielding cards */
UCLASS(BlueprintType, Blueprintable)
class HOTGIRLBASEBALL_API UFieldingDeck : public UHGBBDeck
{
	GENERATED_BODY()

public:
	UFieldingDeck() = default;
	UFieldingDeck(const FFieldingDeckDesc& Descriptor);

	/** The collection of cards spawned and owned by this deck */
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UFieldingCard>> Cards;
};
