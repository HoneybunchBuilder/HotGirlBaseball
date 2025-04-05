// Copyright Ada Tufankjian 2025


#include "PitchingComponent.h"

UPitchingComponent::UPitchingComponent()
{
}

void UPitchingComponent::BeginWindUp()
{
	if (!bCanPitch)
	{
		return;
	}
	OnPitchBegin.Broadcast();
}

void UPitchingComponent::ContinueWindUp(double ElapsedSeconds)
{
	if (!bCanPitch)
	{
		return;
	}
	OnPitchWindingUp.Broadcast(ElapsedSeconds);
}

void UPitchingComponent::ReleaseWindUp(double ElapsedSeconds)
{
	if (!bCanPitch)
	{
		return;
	}
	OnPitchReleased.Broadcast(ElapsedSeconds);
}

float UPitchingComponent::CalcAlpha(double ElapsedSeconds) const
{
	return (ElapsedSeconds * WindUpSpeed) / IdealReleaseTime;
}
