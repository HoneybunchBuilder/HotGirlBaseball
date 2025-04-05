// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PitchingComponent.generated.h"


/** Common functionality for AI and Players to control pitching */
UCLASS()
class HOTGIRLBASEBALL_API UPitchingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPitchingComponent();

	/** Owner should call to start a pitch */
	UFUNCTION(BlueprintCallable)
	void BeginWindUp();

	/** Owner should call every frame that it wants to continue charging the pitch */
	UFUNCTION(BlueprintCallable)
	void ContinueWindUp(double ElapsedSeconds);

	/** Owner calls this to release the pitch */
	UFUNCTION(BlueprintCallable)
	void ReleaseWindUp(double ElapsedSeconds);

	/** Scales how quickly the swing charges power */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float WindUpSpeed = 1.0f;

	/** The ideal elapsed time to release the pitch at for maximum power before WindUpSpeed is applied */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double IdealReleaseTime = 3.0;

	/** Called when the owner begins pitching  */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPitchBegin);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FOnPitchBegin OnPitchBegin;

	/** Called every frame that the pitch is winging up */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPitchWindingUp, double, Alpha);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FOnPitchWindingUp OnPitchWindingUp;

	/** Called when the owner releases the pitch */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPitchReleased, double, Alpha);
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FOnPitchReleased OnPitchReleased;

	/** Controls whether or not the component will respond to calls from the owner */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bCanPitch = false;

private:
	/** Normalizes given ElapsedSeconds to a 0-1 range */
	float CalcAlpha(double ElapsedSeconds) const;
};
