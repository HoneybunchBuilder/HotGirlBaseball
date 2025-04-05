// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BattingComponent.generated.h"

/** Common functionality for AI and Players to control batting */
UCLASS()
class HOTGIRLBASEBALL_API UBattingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBattingComponent();

	/** Owner should call to start a swing */
	UFUNCTION(BlueprintCallable)
	void BeginSwing();

	/** Owner should call every frame that it wants to continue charging a swing */
	UFUNCTION(BlueprintCallable)
	void ChargeSwing(double ElapsedSeconds);

	/** Owner calls to commit to the swing */
	UFUNCTION(BlueprintCallable)
	void CommitSwing(double ElapsedSeconds);

	/** Owner calls to balk and not swing */
	UFUNCTION(BlueprintCallable)
	void CancelSwing();

	/** Scales how quickly the swing charges power */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ChargeSpeed = 1.0f;

	/** The ideal time to release the swing at maximum power before ChargeSpeed is applied */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	double IdealReleaseTime = 3.0;

	/** Called when the batter begins charging a swing */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwingBegin);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FOnSwingBegin OnSwingBegin;

	/** Called every frame that the batter is charging a swing */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwingCharging, double, Alpha);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FOnSwingCharging OnSwingCharging;

	/** Called when the batter commits to swing the bat */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwingCommit, double, Alpha);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FOnSwingCommit OnSwingCommit;

	/** Called when the swing is canceled */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwingCancel);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FOnSwingCancel OnSwingCancel;

	/** Controls whether or not the component will respond to calls from the owner */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bCanSwing;

private:
	/** Normalizes given ElapsedSeconds to a 0-1 range */
	float CalcAlpha(double ElapsedSeconds) const;
};

