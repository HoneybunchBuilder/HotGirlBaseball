// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HGBBStrikeZone.generated.h"

/**
	Describes the strike zone that the pitcher and batter aim around
*/
UCLASS()
class HOTGIRLBASEBALL_API AHGBBStrikeZone : public AActor
{
	GENERATED_BODY()
	
public:
	AHGBBStrikeZone();

	/** Retrieve the world space location of the center of the strike zone */
	UFUNCTION(BlueprintCallable)
	const FVector GetStrikeZoneAimLocation() const;

	/** Retrieve the swing hit capsule */
	UFUNCTION(BlueprintCallable)
	const UCapsuleComponent* GetHitCapsule() const;

	/** Retrieve the strike hit box */
	UFUNCTION(BlueprintCallable)
	const UBoxComponent* GetHitBox() const;

private:
	/** The capsule volume that the ball can collide with that the batter aims their swing towards */
	UPROPERTY(EditDefaultsOnly);
	TObjectPtr<UCapsuleComponent> HitCapsule;

	/** The mesh that serves as the visual indicator for the strike zone */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> VisualIndicator;

	/** The box that encompases the entire area that considers a pitch a "strike" */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> HitBox;
};
