// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "HGBBTypes.h"
#include "HGBBDeck.h"
#include "HGBBPlayer.h"
#include "HGBBTeam.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable)
class UHGBBTeam : public UObject
{
	GENERATED_BODY()

public:
	UHGBBTeam() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor PrimaryColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor SecondaryColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor TertiaryColor;
};

/*
	A LoadoutPreset defines the subclasses that make up a specific loadout

	It's important that this is a UObject, not just a struct, so that it can be assigned to a List View
*/
UCLASS(Abstract, BlueprintType, Blueprintable)
class UHGBBLoadoutPreset : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UHGBBTeam> Team;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EFieldingPosition, TSubclassOf<UHGBBPlayer>> Lineup;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBattingDeckPreset> BattingDeck;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UFieldingDeckPreset> FieldingDeck;
};

/*
	Defines the loadout of a particular team. Not just the Team stylings but also the players, their positions and the selected decks
*/
UCLASS(BlueprintType, Blueprintable)
class UHGBBLoadout : public UObject
{
	GENERATED_BODY()

public:
	UHGBBLoadout() = default;

	UFUNCTION(BlueprintCallable)
	void InitFromPreset(const UHGBBLoadoutPreset* Preset);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UHGBBTeam> Team;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EFieldingPosition, TObjectPtr<UHGBBPlayer>> Lineup;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBattingDeck> BattingDeck;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UFieldingDeck> FieldingDeck;
};

/* A data table row struct that points to a specific Team subclass */
USTRUCT(BlueprintType)
struct FHGBBTeamRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UHGBBTeam> Team;
};

/* A data table row struct that points to a specific LoadoutPreset subclass */
USTRUCT(BlueprintType)
struct FHGBBLoadoutPresetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UHGBBLoadoutPreset> LoadoutPreset;
};

