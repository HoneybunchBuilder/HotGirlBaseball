#include "HGBBTeam.h"

void UHGBBLoadout::InitFromPreset(const UHGBBLoadoutPreset* Preset)
{
	check(Preset);
	Team = Preset->Team.GetDefaultObject();
	for (const auto& It : Preset->Lineup)
	{
		Lineup.Emplace(It.Key, It.Value.GetDefaultObject());
	}
	BattingDeck = NewObject<UBattingDeck>(this);
	BattingDeck->InitFromPreset(*Preset->BattingDeck.GetDefaultObject());
	FieldingDeck = NewObject<UFieldingDeck>(this);
	FieldingDeck->InitFromPreset(*Preset->FieldingDeck.GetDefaultObject());
}
