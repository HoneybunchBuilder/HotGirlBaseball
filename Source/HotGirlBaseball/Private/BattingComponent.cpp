// Copyright Ada Tufankjian 2025


#include "BattingComponent.h"

UBattingComponent::UBattingComponent()
{
}

void UBattingComponent::BeginSwing()
{
	if (!bCanSwing)
	{
		return;
	}
	OnSwingBegin.Broadcast();
}

void UBattingComponent::ChargeSwing(double ElapsedSeconds)
{
	if (!bCanSwing)
	{
		return;
	}
	OnSwingCharging.Broadcast(ElapsedSeconds);
}

void UBattingComponent::CommitSwing(double ElapsedSeconds)
{
	if (!bCanSwing)
	{
		return;
	}
	OnSwingCommit.Broadcast(ElapsedSeconds);
}

void UBattingComponent::CancelSwing()
{
	if (!bCanSwing)
	{
		return;
	}
	OnSwingCancel.Broadcast();
}

float UBattingComponent::CalcAlpha(double ElapsedSeconds) const
{
	return (ElapsedSeconds * ChargeSpeed) / IdealReleaseTime;
}
