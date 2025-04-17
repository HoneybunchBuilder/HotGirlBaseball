// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HGBBTypes.h"
#include "HGBBMapMarkup.generated.h"

class USplineComponent;

class AHGBBBaseMarker;
class AHGBBDugout;
class AHGBBBatterBox;
class AHGBBCameraAnchor;

/**
	An actor that stores references to other actors that mark up various game functions
*/
UCLASS(BlueprintType, Blueprintable)
class HOTGIRLBASEBALL_API AHGBBMapMarkup : public AActor
{
	GENERATED_BODY()
	
public:	
	AHGBBMapMarkup();

	/** Retrieve the marker actor for the given base enum value */
	UFUNCTION(BlueprintCallable)
	AHGBBBaseMarker* GetMarkerForBase(EBase Base) const;

	/** Retrieve the world location of the given base */
	UFUNCTION(BlueprintCallable)
	FVector GetBaseLocation(EBase Base) const;

	/** Retrieve the Dugout actor for the given team type */
	UFUNCTION(BlueprintCallable)
	AHGBBDugout* GetDugout(ETeamType Team) const;

	/** Retrieve the batters box for the given handedness of a player */
	UFUNCTION(BlueprintCallable)
	AHGBBBatterBox* GetBatterBox(EHandedness Handedness) const;

	/** Returns true if a ball reaching the given location would be considered foul */
	UFUNCTION(BlueprintCallable)
	bool IsLocationFoul(const FVector& Location) const;

	/** Returns true if a ball reaching the given location would be a home run */
	UFUNCTION(BlueprintCallable)
	bool IsLocationHomeRun(const FVector& Location) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Closed spline that marks up what is considered the infield */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USplineComponent> Infield;

	/** Closed spline that contains the entire playfield */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USplineComponent> Playfield;

	/** A simple spline that defines the left foul line */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USplineComponent> LeftFoul;

	/** A simple spline that defines the right foul line */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USplineComponent> RightFoul;

private:

	/** A list of every base marker; the index of the marker in the array should correspond with the integer value associated with EBase */
	TArray<TObjectPtr<AHGBBBaseMarker>> BaseMarkers;

	/** A pointer to the home team's dugout */
	TObjectPtr<AHGBBDugout> HomeDugout;

	/** A pointer to the away team's dugout */
	TObjectPtr<AHGBBDugout> AwayDugout;

	/** A pointer to the batting box for right handed batters */
	TObjectPtr<AHGBBBatterBox> BatterBoxRH;

	/** A pointer to the batting box for left handed batters */
	TObjectPtr<AHGBBBatterBox> BatterBoxLH;

	/** A list of all available camera anchor points around the map */
	TArray<AHGBBCameraAnchor> CameraAnchors;
};
