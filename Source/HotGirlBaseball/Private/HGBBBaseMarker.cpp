// Copyright Ada Tufankjian 2025


#include "HGBBBaseMarker.h"

AHGBBBaseMarker::AHGBBBaseMarker()
{
}

EBase AHGBBBaseMarker::GetBase() const
{
	return Base;
}

void AHGBBBaseMarker::SetGuardingPawn(AFieldingPawn* Pawn)
{
	GuardingPawn = Pawn;
}

bool AHGBBBaseMarker::IsGuarded() const
{
	return GuardingPawn.IsValid();
}

