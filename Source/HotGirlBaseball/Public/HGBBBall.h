// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"

#include "HGBBTypes.h"

#include "HGBBBall.generated.h"

class UNiagaraComponent;
class UProjectileMovementComponent;
class UMetaSoundSource;
class AHGBBStrikeZone;
class AHGBBMapMarkup;

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

	// Some public debugging properties

	UPROPERTY(BlueprintReadWrite)
	bool DebugHitOverride = false;

	UPROPERTY(BlueprintReadWrite)
	float DebugHorizontalAlpha = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float DebugVerticalAlpha = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float DebugHitPower = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	bool DebugPitchOverride = false;

	UPROPERTY(BlueprintReadWrite)
	bool DebugPitchBallOrStrike = false;

	UPROPERTY(BlueprintReadWrite)
	bool DebugPitchVariable = false;

	UPROPERTY(BlueprintReadWrite)
	float DebugPitchVariation = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float DebugPitchReleaseAlpha = 0.0f;

protected:
	virtual void BeginPlay() override;

public:
	/** Get whether or not the ball is currently live and in play */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	bool GetLive() const;

	/** Get whether or not the ball has been hit by the batter */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	bool GetHit() const;

	/** Get whether or not the ball should connect to the bat shortly */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	bool GetShouldHit() const;

	/** Get the type of hit the batter made on the ball */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	FHitType GetHitType() const;

	/** Get whether or not the ball can be considered a strike */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	bool GetStrike() const;

	/** Get whether or not the ball has landed after being hit by the batter */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	bool GetHitLanded() const;

	/** Get the expected landing point of the ball after being hit */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	FVector GetHitLandingLocation() const;

	/** Overriding AActor::GetVelocity */
	virtual FVector GetVelocity() const override;

	/** Finish the current play and reset the ball */
	UFUNCTION(BlueprintCallable)
	void FinishPlay();

	/** Instruct the ball actor that it is being pitched to a target location */
	UFUNCTION(BlueprintCallable)
	void Pitch(float ReleaseAlpha, const FVector& Target);

	/** Instruct the ball that it is being passed to a target location */
	UFUNCTION(BlueprintCallable)
	void Pass(const FVector& Target);

	/** Call when a fielder catches the ball and we need to attach to a point on the fielder */
	UFUNCTION(BlueprintCallable)
	void FielderCatches(USceneComponent* AttachComponent, const FName& Socket);

	/** Based on the given swing reponse time determine if the ball should contact the bat and if so the ball will redirect its velocity to make the impact more visibly consistant */
	UFUNCTION(BlueprintCallable)
	void DetermineAndRedirectHit2(float BatTimeToContactPoint);

	/** Broadcasts when the play has resolved and FinishPlay has been called */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayFinished);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FPlayFinished PlayFinished;

	/** Broadcasts when the ball is either hit or reset */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayStateChanged, bool, Hit);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FPlayStateChanged PlayStateChanged;

	/** Broadcasts the first time a ball lands after being hit */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitLands);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FHitLands HitLands;

	/** Broadcasts if a ball is caught before landing and should result in an out */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitCaught);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FHitCaught HitCaught;

	/** Broadcasts any time the ball hits the ground*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBallHitsGround);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FBallHitsGround BallHitsGround;

	/** Broadcasts when a hit is declared a Foul */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFoulBall);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FFoulBall FoulBall;

	/** Broadcasts when a hit is declared a home run */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHomeRun);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FHomeRun HomeRun;

private:
	void ThrowBallToLocation(const FVector& Target, float LaunchSpeed);

	/** Response to ball mesh getting hit */
	UFUNCTION()
	void OnCollisionHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Response to ball mesh overlapping */
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** Activate the throw particle effect with the given alpha as an input */
	void ActivateThrowEffect2(float Alpha);

	/** Generate a hit response based on the given contact point */
	void GenerateHit(const FVector& HitPos);

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

	/** The sound source to use when the ball is thrown */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMetaSoundSource> ThrownSoundSource;

	/** The sound source to use when the ball is hit */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMetaSoundSource> HitSoundSource;

	/** Timing threshold for ball to be redirected to new target when batter swings */
	UPROPERTY(EditDefaultsOnly)
	float RedirectTimingThreshold = 0.18f;

	/** Threshold in vertical alpha required for a hit to be considered a line drive */
	UPROPERTY(EditDefaultsOnly)
	float GroundBallThreshold = -0.2f;

	/** Threshold in vertical alpha required for a hit to be considered a line drive */
	UPROPERTY(EditDefaultsOnly)
	float LineDriveThreshold = 0.1f;

	/** Threshold in horizontal alpha required for a hit to be considered aimed towards center field */
	UPROPERTY(EditDefaultsOnly)
	float CenterFieldThreshold = 0.1f;

	/** Pointer to the strike zone fetched from the world on BeginPlay */
	TObjectPtr<AHGBBStrikeZone> StrikeZone;

	/** Pointer to the map markup helper actor fected from the workd on BeginPlay */
	TObjectPtr<AHGBBMapMarkup> MapMarkup;

	// TODO: These state booleans could be merged into a state bitfield

	/** Is the ball currently in a state where it *should* connect and result in a hit but hasn't yet */
	bool bShouldHit = false;

	/** Has the ball been hit by the batter yet */
	bool bHit = false;

	/** Has the hit landed on the ground at least once */
	bool bHitLanded = false;

	/** Is the ball currently live and in play */
	bool bLive = false;

	/** Has the ball contacted the strike zone yet during its travel */
	bool bStrike = false;

	/** Has the ball been marked foul */
	bool bFoul = false;

	/** Is the ball currently in a state where being caught would result in an out */
	bool bCanCatchOut = false;

	/** Is the ball currently in the air */
	bool bInAir = false;

	/** Launch velocity of the ball when it was last thrown */
	FVector LaunchVelocity = FVector::ZeroVector;

	/** The expected landing point of the ball after being hit */
	FVector HitLandingLocation = FVector::ZeroVector;

	/** The current target location that the ball is aiming to travel to */
	FVector ThrowTarget = FVector::ZeroVector;

	/** The time in seconds when the ball was last thrown */
	double TimeThrown = 0.0;

	/** The estimated amount of time in seconds it will take for the ball to reach its current target from its starting point */
	double TimeToTarget = 0.0;

	/** Info about the direction and arc of the last time this ball was hit */
	FHitType HitType = {};
};
