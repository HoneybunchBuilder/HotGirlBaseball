// Copyright Ada Tufankjian 2025


#include "HGBBMovement.h"

UHGBBMovement::UHGBBMovement()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHGBBMovement::BeginPlay()
{
	Super::BeginPlay();
}

void UHGBBMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
