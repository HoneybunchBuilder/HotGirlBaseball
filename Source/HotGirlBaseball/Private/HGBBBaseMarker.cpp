// Copyright Ada Tufankjian 2025


#include "HGBBBaseMarker.h"

#include "GameFramework/Pawn.h"

AHGBBBaseMarker::AHGBBBaseMarker()
{
}

EBase AHGBBBaseMarker::GetBase() const
{
	return Base;
}

void AHGBBBaseMarker::SetGuardingPawn(APawn* Pawn)
{
	GuardingPawn = Pawn;
}

const APawn* AHGBBBaseMarker::GetGuardingPawn() const
{
	return GuardingPawn.Get();
}

bool AHGBBBaseMarker::IsGuarded() const
{
	return GuardingPawn.IsValid();
}

