// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemInterface.h"
#include "NiagaraComponent.h"

#include "HGBBTypes.h"

#include "HGBBBall.generated.h"

/**
	The Ball actor for this baseball game
*/
UCLASS(BlueprintType, Blueprintable)
class HOTGIRLBASEBALL_API AHGBBBall : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AHGBBBall();

	//~ Begin IAbilitySystemInterface
	/** Returns our Ability System Component. */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface

protected:
	virtual void BeginPlay() override;

public:
	/** Instruct the ball actor that it is being pitched to a target location */
	UFUNCTION(BlueprintCallable)
	void Pitch(float ReleaseAlpha, const FVector& Target);

	/** Instruct the ball that it is being passed to a target location */
	UFUNCTION(BlueprintCallable)
	void Pass(const FVector& Target);
	
	/** When the ball has been acquired by a pawn this will be called to potentially call the current batter out */
	UFUNCTION(BlueprintCallable)
	void TryCatchOut2();

	/** Based on the given swing reponse time determine if the ball should contact the bat and if so the ball will redirect its velocity to make the impact more visibly consistant */
	UFUNCTION(BlueprintCallable)
	void DetermineAndRedirectHit2(float BatTimeToContactPoint);

private:
	/** Visual Logging helper for debugging hits */
	void HitResultVisLogStart2(float EstTimeToHit);

	/** Activate the throw particle effect with the given alpha as an input */
	void ActivateThrowEffect2(float Alpha);

	/** Calculate the time in seconds to the ball's current target location */
	float CalcTimeToTarget2();

	/** Calculate the time in seconds to the given target location based on the given launch velocity */
	float GetProjectileToTargetTime(const FVector& Target, const FVector& LaunchVelocity);

	/** Set the Live status of the ball */
	void SetLive(bool bLive);

	/** Set the Hit status of the ball */
	void SetHit(bool bHit);

	/** Generate a hit response based on the given contact point */
	FHitType GenerateHit2(const FVector& HitPos);

	/** The display mesh for the ball */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;

	/** The particle effect to play when the ball is pitched*/
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraComponent> PitchEffect;

	/** The ribbon effect that trails the ball to enhance readability of the ball's trajectory and location*/
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraComponent> TravelRibbon;

	/** The particle effect to play when the batter hits the ball */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraComponent> HitEffect;

	/** Movement component that drives the ball as it flys through the air */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	/** The underlying ability component to drive special gameplay effects specific to the ball */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAbilitySystemComponent> AbilityComponent;
};
