// Copyright Ada Tufankjian 2025


#include "HGBBDeck.h"
#include "Algo/RandomShuffle.h"

void UBattingDeck::InitFromPreset(const UBattingDeckPreset& Preset)
{
	DisplayName = Preset.DisplayName;
	Icon = Preset.Icon;
	for (const auto& It : Preset.BattingCards)
	{
		const int32 NumCardType = It.Value;
		for (int32 Index = 0; Index < NumCardType; ++Index)
		{
			auto Card = NewObject<UBattingCard>(this, It.Key);
			Cards.Add(Card);
		}
	}
	Shuffle();
}

void UBattingDeck::Shuffle()
{
	Algo::RandomShuffle(Cards);
}

void UFieldingDeck::InitFromPreset(const UFieldingDeckPreset& Preset)
{
	DisplayName = Preset.DisplayName;
	Icon = Preset.Icon;
	for (const auto& It : Preset.FieldingCards)
	{
		const int32 NumCardType = It.Value;
		for (int32 Index = 0; Index < NumCardType; ++Index)
		{
			auto Card = NewObject<UFieldingCard>(this, It.Key);
			Cards.Add(Card);
		}
	}
	Shuffle();
}

void UFieldingDeck::Shuffle()
{
	Algo::RandomShuffle(Cards);
}
