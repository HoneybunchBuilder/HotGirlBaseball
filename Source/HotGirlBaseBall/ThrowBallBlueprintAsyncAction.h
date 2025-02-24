// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "FieldingAIController.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ThrowBallBlueprintAsyncAction.generated.h"

/**
 * Signatures of execution pins in the editor
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FThrowCompleteOutputPin);

/**
 * Latent action for instructing a fielder to throw the ball to a target
 */
UCLASS()
class HOTGIRLBASEBALL_API UThrowBallBlueprintAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

private:
	AFieldingAIController* AIController;

	const APawn* Target;

	UFUNCTION()
	void ThrowCompleted();
	
public:
	UPROPERTY(BlueprintAssignable)
	FThrowCompleteOutputPin Completed;

	/**
	 * InternalUseOnly to hide sync version in BPs
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "AsyncNode")
	static UThrowBallBlueprintAsyncAction* AIThrowBallTo(AFieldingAIController* Controller, const APawn* Target);

	virtual void Activate() override;
};
