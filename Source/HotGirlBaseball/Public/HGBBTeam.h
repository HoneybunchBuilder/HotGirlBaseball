// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "HGBBTeam.generated.h"

USTRUCT(BlueprintType)
struct FHGBBTeam
{
	GENERATED_BODY()

	FName Name;
	FText DisplayName;
	TObjectPtr<UTexture2D> Icon;
	FLinearColor PrimaryColor;
	FLinearColor SecondaryColor;
	FLinearColor TertiaryColor;
};