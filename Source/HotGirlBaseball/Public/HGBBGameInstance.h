// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "HGBBGameInstance.generated.h"

/**
 * We override the game instance to have more control over lifetimes for things like loading screens
 */
UCLASS()
class HOTGIRLBASEBALL_API UHGBBGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
};
