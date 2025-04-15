// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "HGBBCard.h"
#include "HGBBDeck.generated.h"

UCLASS(BlueprintType)
class UHGBBDeckPreset : public UObject
{
	GENERATED_BODY()

public:
	UHGBBDeckPreset() = default;

	/** The user-facing name of this deck */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText DisplayName;

	/** The user-facing icon that represents this deck in the UI */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon;
};

UCLASS(BlueprintType, Blueprintable)
class UBattingDeckPreset : public UHGBBDeckPreset
{
	GENERATED_BODY()

public:
	UBattingDeckPreset() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<TSubclassOf<UBattingCard>, int32> BattingCards;
};

USTRUCT(BlueprintType)
struct FBattingDeckPresetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBattingDeckPreset> Preset;
};

UCLASS(BlueprintType, Blueprintable)
class UFieldingDeckPreset : public UHGBBDeckPreset
{
	GENERATED_BODY()

public:
	UFieldingDeckPreset() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<TSubclassOf<UFieldingCard>, int32> FieldingCards;
};


USTRUCT(BlueprintType)
struct FFieldingDeckPresetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UFieldingDeckPreset> Preset;
};

/** A Collection of cards along with some metadata */
UCLASS(Abstract, BlueprintType, Blueprintable)
class UHGBBDeck : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void Shuffle() {};

	UFUNCTION(BlueprintCallable)
	virtual TArray<UHGBBCard*> GetCards() const { return {}; }

	/** The user-facing name of this deck */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText DisplayName;

	/** The user-facing icon that represents this deck in the UI */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UTexture2D> Icon;
};

/** A Collection of batting cards */
UCLASS(BlueprintType)
class UBattingDeck : public UHGBBDeck
{
	GENERATED_BODY()

public:
	UBattingDeck() = default;

	void InitFromPreset(const UBattingDeckPreset& Preset);

	virtual void Shuffle() override;

	virtual TArray<UHGBBCard*> GetCards() const override;

	/** The collection of cards spawned and owned by this deck */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TObjectPtr<UBattingCard>> Cards;
};

/** A Collection of fielding cards */
UCLASS(BlueprintType)
class UFieldingDeck : public UHGBBDeck
{
	GENERATED_BODY()

public:
	UFieldingDeck() = default;

	void InitFromPreset(const UFieldingDeckPreset& Preset);

	virtual void Shuffle() override;

	virtual TArray<UHGBBCard*> GetCards() const override;

	/** The collection of cards spawned and owned by this deck */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TObjectPtr<UFieldingCard>> Cards;
};

