// Copyright Ada Tufankjian 2025


#include "HGBBStrikeZone.h"

AHGBBStrikeZone::AHGBBStrikeZone()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	HitCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hit Capsule"));
	HitCapsule->SetupAttachment(RootComponent);

	VisualIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Indicator"));
	VisualIndicator->SetupAttachment(RootComponent);

	// The hitbox should follow the visual indicator but its size is expected to be manually tuned
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit Box"));
	HitBox->SetupAttachment(VisualIndicator);

	PrimaryActorTick.bCanEverTick = false;
}

const FVector AHGBBStrikeZone::GetStrikeZoneAimLocation() const
{
	return VisualIndicator->GetComponentLocation();
}

const UCapsuleComponent* AHGBBStrikeZone::GetHitCapsule() const
{
	return HitCapsule;
}

const UBoxComponent* AHGBBStrikeZone::GetHitBox() const
{
	return HitBox;
}
