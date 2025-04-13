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

UCLASS(Abstract, BlueprintType, Blueprintable)
class UHGBBLoadout : public UObject
{
	GENERATED_BODY()

public:
	UHGBBLoadout() = default;

	void InitFromPreset(const FHGBBLoadoutRow& Preset);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UHGBBTeam> Team;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EFieldingPosition, TObjectPtr<UHGBBPlayer>> Lineup;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBattingDeck> BattingDeck;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UFieldingDeck> FieldingDeck;
};

USTRUCT(BlueprintType)
struct FHGBBTeamRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHGBBTeam> Team;
};

USTRUCT(BlueprintType)
struct FHGBBLoadoutRow : public FTableRowBase 
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UHGBBTeam> Team;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EFieldingPosition, TSubclassOf<UHGBBPlayer>> Lineup;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBattingDeckPreset> BattingDeck;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UFieldingDeckPreset> FieldingDeck;
};

