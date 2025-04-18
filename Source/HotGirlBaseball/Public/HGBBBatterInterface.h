// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "HGBBBatterInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UHGBBBatterInterface : public UInterface
{
	GENERATED_BODY()
};

/** A temporary interface for driving the WIP batting pawn BP from the new C++ core */
class IHGBBBatterInterface 
{
	GENERATED_BODY()
public:
	/** Implemented in Blueprint to allow BP version of batter to consume this command from C++ */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnReturnToDugout();
};
