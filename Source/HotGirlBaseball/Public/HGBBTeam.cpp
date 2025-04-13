#include "HGBBTeam.h"

void UHGBBLoadout::InitFromPreset(const FHGBBLoadoutRow& Preset)
{
	Team = Preset.Team.GetDefaultObject();
	for (const auto& It : Preset.Lineup)
	{
		Lineup.Emplace(It.Key, It.Value.GetDefaultObject());
	}
	BattingDeck->InitFromPreset(*Preset.BattingDeck.GetDefaultObject());
	FieldingDeck->InitFromPreset(*Preset.FieldingDeck.GetDefaultObject());
}
