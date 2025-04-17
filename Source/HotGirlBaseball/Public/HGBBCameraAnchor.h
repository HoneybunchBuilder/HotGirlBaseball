// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HGBBCameraAnchor.generated.h"

/**
	An actor that marks up a location that a camera can be placed at to achieve a particular shot
*/
UCLASS(BlueprintType, Blueprintable)
class HOTGIRLBASEBALL_API AHGBBCameraAnchor : public AActor
{
	GENERATED_BODY()
	
public:	
	AHGBBCameraAnchor();
};
