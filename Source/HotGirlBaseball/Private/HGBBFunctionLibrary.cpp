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
