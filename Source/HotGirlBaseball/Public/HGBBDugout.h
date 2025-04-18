// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HGBBTypes.h"
#include "HGBBTeam.h"
#include "HGBBDugout.generated.h"

class UArrowComponent;
class USphereComponent;

class ABattingPawn;

/**
	An actor that marks up a dugout where batters will be placed when they are not at bat
*/
UCLASS(BlueprintType, Blueprintable)
class HOTGIRLBASEBALL_API AHGBBDugout : public AActor
{
	GENERATED_BODY()

public:
	AHGBBDugout();

	/** Get a reference to exactly which team this dugout belongs to at the moment */
	UFUNCTION(BlueprintCallable)
	UHGBBTeam* GetTeam() const;

	/** Get whether this dugout belongs to the home or away team */
	UFUNCTION(BlueprintCallable)
	ETeamType GetTeamType() const;

	/** Place the given batters in their appropriate positions */
	UFUNCTION(BlueprintCallable)
	void ResetBatters(UPARAM(ref) TArray<APawn*>& Batters);

protected:
	/** Indicates the overall forward facing direction of all the relevant spots for the dugout */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> Forward;

	/** The number of spots to generate */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 NumSpots = 9;

	/** The amount of space to leave between each spot marker */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SpotSpacing;

	/** An array of all possible places to relocate a batter to */
	UPROPERTY(BlueprintReadOnly)
	TArray<USceneComponent*> Spots;

	/** The details of the team this dugout is for */
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UHGBBTeam> Team;

private:
	/** Whether this dugout is for the home or away team */
	UPROPERTY(EditInstanceOnly)
	ETeamType TeamType;
};
