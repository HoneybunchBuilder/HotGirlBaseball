#include "HGBBGameInstance.h"

#include "ShaderPipelineCache.h"
#include "HGBBUserSettings.h"

void UHGBBGameInstance::Init()
{
	Super::Init();
}

int32 UHGBBGameInstance::GetNumShadersCompiling() const
{
	return FShaderPipelineCache::NumPrecompilesRemaining();
}

void UHGBBGameInstance::OnIntroSequenceBegun()
{
	check(bIntroSequenceStarted == false);
	bIntroSequenceStarted = true;
}

bool UHGBBGameInstance::HasIntroSequenceBegun() const
{
	// If the user does not want the intro, we just lie and say it's already over
	if (auto Settings = Cast<UHGBBUserSettings>(UGameUserSettings::GetGameUserSettings()))
	{
		if (Settings->GetSkipIntro())
		{
			return true;
		}
	}
	return bIntroSequenceStarted;
}

void UHGBBGameInstance::HoldLoadingScreen(bool bHold)
{
	bHoldLoadingScreen = bHold;
}

bool UHGBBGameInstance::ShouldHoldLoadingScreen() const
{
	return bHoldLoadingScreen;
}

bool UHGBBGameInstance::ShouldShowLoadingScreen(FString& OutReason) const
{
	if (ShouldHoldLoadingScreen())
	{
		OutReason = TEXT("HGBBGameInstanced is holding the loading screen");
		return true;
	}
	return false;
}
