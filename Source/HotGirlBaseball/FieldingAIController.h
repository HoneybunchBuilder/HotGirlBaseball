// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FieldingAIController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAIBallThrownDelegate);

/**
 * AI Controller for the Fielding Pawn
 */
UCLASS()
class HOTGIRLBASEBALL_API AFieldingAIController : public AAIController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ThrowBallTo(const APawn* Target) const;

	UPROPERTY(BlueprintCallable)
	FAIBallThrownDelegate AIBallThrown;
};
