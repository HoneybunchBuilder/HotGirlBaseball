// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "HGBBUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class HOTGIRLBASEBALL_API UHGBBUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
	
public:
	// Get the user's preference about skipping the intro sequence
	UFUNCTION(BlueprintPure)
	virtual bool GetSkipIntro() const;

	// Set the user's preference about skipping the intro sequence
	UFUNCTION(BlueprintCallable)
	virtual void SetSkipIntro(bool bInSkipIntro);

private:
	// Set to true if the user doesn't want to see the intro sequence
	UPROPERTY(EditAnywhere, Config)
	bool bSkipIntro = false;
};
