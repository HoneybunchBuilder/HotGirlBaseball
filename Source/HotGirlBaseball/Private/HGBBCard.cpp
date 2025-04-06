// Copyright Ada Tufankjian 2025


#include "HGBBCard.h"

UBattingCard::UBattingCard()
{
	if (Ability)
	{
		AbilityPtr = NewObject<UBattingAbility>(this, Ability);
	}
}

UFieldingCard::UFieldingCard()
{
	if (Ability)
	{
		AbilityPtr = NewObject<UFieldingAbility>(this, Ability);
	}
}
