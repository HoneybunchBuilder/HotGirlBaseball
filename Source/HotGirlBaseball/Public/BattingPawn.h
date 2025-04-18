// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BattingPawn.generated.h"

/** A Player controllable pawn responsible for batting and running bases */
UCLASS()
class HOTGIRLBASEBALL_API ABattingPawn : public APawn
{
	GENERATED_BODY()

public:
	ABattingPawn();
	
	/** Call when a batting pawn is being sent to a spot in their dugout */
	UFUNCTION(BlueprintCallable)
	void OnReturnToDugout();

protected:
	virtual void BeginPlay() override;
};
