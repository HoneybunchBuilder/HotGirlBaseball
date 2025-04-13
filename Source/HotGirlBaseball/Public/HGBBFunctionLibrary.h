// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/Widget.h"
#include "HGBBTypes.h"
#include "HGBBDeck.h"

#include "HGBBFunctionLibrary.generated.h"

/**
 * A helper function library for Hot Girl Baseball
 */
UCLASS()
class HOTGIRLBASEBALL_API UHGBBFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Get the currently focused widget
	UFUNCTION(BlueprintCallable)
	static UWidget* GetFocusedWidget();

	// Look up if the given position is currently responsible for the current base
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool DoesPositionGuardBase(EFieldingPosition Position, EBase Base);

	// Get priority order from base
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static int32 GetBasePriority(EBase Base);

	// Get base from priority order
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static EBase GetBaseFromPriority(int32 Priority);
};
