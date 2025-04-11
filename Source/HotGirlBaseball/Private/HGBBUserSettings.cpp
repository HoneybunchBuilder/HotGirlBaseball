// Copyright Ada Tufankjian 2025


#include "HGBBUserSettings.h"

bool UHGBBUserSettings::GetSkipIntro() const
{
	return bSkipIntro;
}

void UHGBBUserSettings::SetSkipIntro(bool bInSkipIntro)
{
	bSkipIntro = bInSkipIntro;
	SaveSettings();
}
