// Copyright Ada Tufankjian 2025


#include "HGBBFunctionLibrary.h"


UWidget* UHGBBFunctionLibrary::GetFocusedWidget()
{
	// See https://georgy.dev/posts/get-focused-widget/

	TSharedPtr<SWidget> FocusedSlateWidget = FSlateApplication::Get().GetUserFocusedWidget(0);
	if (!FocusedSlateWidget.IsValid())
	{
		return nullptr;
	}
	for (TObjectIterator<UWidget> Itr; Itr; ++Itr)
	{
		UWidget* CandidateUMGWidget = *Itr;
		if (CandidateUMGWidget->GetCachedWidget() == FocusedSlateWidget)
		{
			return CandidateUMGWidget;
		}
	}

	return nullptr;
}

bool UHGBBFunctionLibrary::DoesPositionGuardBase(EFieldingPosition Position, EBase Base)
{
	// Some roles currently don't have any responsbility to guard a base
	// We probably want this to be more dynamic; i.e. if first base is out of commission due to some ability the right fielder could cover
	// Also consider short stop covering second or third depending on the play

	if (Position == EFieldingPosition::FirstBase && Base == EBase::First)
	{
		return true;
	}
	if (Position == EFieldingPosition::SecondBase && Base == EBase::Second)
	{
		return true;
	}
	if (Position == EFieldingPosition::ThirdBase && Base == EBase::Third)
	{
		return true;
	}

	return false;
}

int32 UHGBBFunctionLibrary::GetBasePriority(EBase Base)
{
	switch (Base)
	{
	case EBase::First:
		return 0;
	case EBase::Second:
		return 1;
	case EBase::Third:
		return 2;
	default:
	case EBase::Home:
		return 3;
	}
}

EBase UHGBBFunctionLibrary::GetBaseFromPriority(int32 Priority)
{
	switch (Priority)
	{
	case 0:
		return EBase::First;
	case 1:
		return EBase::Second;
	case 2:
		return EBase::Third;
	case 3:
	default:
		return EBase::Home;
	}
}
