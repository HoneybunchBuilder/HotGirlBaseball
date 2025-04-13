// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "HGBBCard.h"
#include "Blueprint/UserWidget.h"
#include "CardWidgetBase.generated.h"

/** A C++ API to interface with the card widget*/
UCLASS()
class HOTGIRLBASEBALL_API UCardWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ApplyCardStyle(const UHGBBCard* Card);
};
