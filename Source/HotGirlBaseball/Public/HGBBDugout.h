// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HGBBTypes.h"
#include "HGBBTeam.h"
#include "HGBBDugout.generated.h"

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

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UHGBBTeam> Team;

private:
	UPROPERTY(EditInstanceOnly)
	ETeamType TeamType;
};
