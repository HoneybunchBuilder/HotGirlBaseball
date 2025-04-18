// Copyright Ada Tufankjian 2025


#include "HGBBDugout.h"

#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"

#include "BattingPawn.h"

AHGBBDugout::AHGBBDugout()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Forward = CreateDefaultSubobject<UArrowComponent>(TEXT("Foward"));
	Forward->SetupAttachment(RootComponent);

	auto SpotName = FString(TEXT("SpotX")); // Reserve a name string that we can re-use in the loop
	// Create a component for each possible spot in the dugout a batter can be sent to
	Spots.Reserve(NumSpots);
	for (int32 SpotIndex = 0; SpotIndex < NumSpots; SpotIndex++)
	{
		SpotName = FString::Printf(TEXT("Spot%d"), SpotIndex);
		auto SpotComponent = CreateDefaultSubobject<USphereComponent>(*SpotName);
		SpotComponent->SetRelativeLocation(FVector(SpotIndex * SpotSpacing));
		SpotComponent->SetSphereRadius(32.0f);
		SpotComponent->SetupAttachment(RootComponent);
		Spots.Add(SpotComponent);
	}
}

UHGBBTeam* AHGBBDugout::GetTeam() const
{
	return Team;
}

ETeamType AHGBBDugout::GetTeamType() const
{
	return TeamType;
}

void AHGBBDugout::ResetBatters(UPARAM(ref)TArray<APawn*>& Batters)
{
	// We can't handle more batters than we have spots
	check(Batters.Num() <= Spots.Num());
	/*
		In the order provided, place each given batter at the Spot marker at the same index
	*/
	const auto& ForwardRelativeTransform = Forward->GetRelativeTransform();
	for (int32 BatterIndex = 0; BatterIndex < Batters.Num(); BatterIndex++)
	{
		auto& Batter = Batters[BatterIndex];
		// TODO: Not yet
		//Batter->OnReturnToDugout();
		
		const auto& Spot = Spots[BatterIndex];
		const auto& SpotTransform = Spot->GetComponentTransform();

		const auto TargetTransform = ForwardRelativeTransform * SpotTransform;
		Batter->SetActorLocationAndRotation(TargetTransform.GetLocation(), TargetTransform.GetRotation());
	}
}

