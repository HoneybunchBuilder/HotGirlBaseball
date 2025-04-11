// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LoadingProcessInterface.h"
#include "Blueprint/UserWidget.h"
#include "HGBBGameInstance.generated.h"

/**
 * We override the game instance to have more control over lifetimes for things like loading screens
 */
UCLASS()
class HOTGIRLBASEBALL_API UHGBBGameInstance : public UGameInstance, public ILoadingProcessInterface
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	// Caller wants to know how many shaders are compiling currently
	UFUNCTION(BlueprintPure)
	virtual int32 GetNumShadersCompiling() const;

	// Caller wants to mark that the player has begun the intro sequence
	UFUNCTION(BlueprintCallable)
	virtual void OnIntroSequenceBegun();

	// Caller wants to know if the intro sequence has started yet
	UFUNCTION(BlueprintPure)
	virtual bool HasIntroSequenceBegun() const;

	// Caller is asking for the loading screen to be held
	UFUNCTION(BlueprintCallable)
	virtual void HoldLoadingScreen(bool bHold);

	// Returns true if the game instance has been asked to hold the loading screen
	UFUNCTION(BlueprintPure)
	virtual bool ShouldHoldLoadingScreen() const;

	// ILoadingProcessInterface Begin
	virtual bool ShouldShowLoadingScreen(FString& OutReason) const override;
	// ILoadingProcessInterface End
private:
	bool bIntroSequenceStarted = false;
	bool bHoldLoadingScreen = false;
};
