// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/Widget.h"

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
};
