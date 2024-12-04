#include "HotGirlBaseballGameInstance.h"

#include "MoviePlayer.h"

void UHotGirlBaseballGameInstance::Init()
{
	Super::Init();

	check(LoadingScreenClass);

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UHotGirlBaseballGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UHotGirlBaseballGameInstance::EndLoadingScreen);
}

void UHotGirlBaseballGameInstance::BeginLoadingScreen(const FString& MapName)
{
	// Shouldn't be relevant but just being cautious
	if (IsRunningDedicatedServer())
	{
		return;
	}
	if (LoadingScreenClass == nullptr)
	{
		return;
	}

	UUserWidget* LoadingScreenWidget = CreateWidget<UUserWidget>(this, LoadingScreenClass);
	if (LoadingScreenWidget == nullptr)
	{
		return;
	}

	FLoadingScreenAttributes LoadingScreenSettings = {};
	LoadingScreenSettings.MinimumLoadingScreenDisplayTime = 1.0f;
	LoadingScreenSettings.bMoviesAreSkippable = false;
	LoadingScreenSettings.bAutoCompleteWhenLoadingCompletes = false;
	LoadingScreenSettings.WidgetLoadingScreen = LoadingScreenWidget->TakeWidget();

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenSettings);
}

void UHotGirlBaseballGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
}
