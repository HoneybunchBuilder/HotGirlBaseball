// Copyright Ada Tufankjian 2025


#include "HGBBDeck.h"
#include "Algo/RandomShuffle.h"

UHGBBDeck::UHGBBDeck(const FHGBBDeckDesc& Descriptor)
	: DisplayName(Descriptor.DisplayName)
	, Icon(Descriptor.Icon)
{
}

UBattingDeck::UBattingDeck(const FBattingDeckDesc& Descriptor)
	: UHGBBDeck(Descriptor)
{
	for (const auto& CardType : Descriptor.CardTypes)
	{
		auto Type = CardType.Key;
		int32 Num = CardType.Value;
		for (int32 CardIndex = 0; CardIndex < Num; ++CardIndex)
		{
			auto Card = NewObject<UBattingCard>(this, Type);
			Cards.Add(Card);
		}
	}

	Algo::RandomShuffle(Cards);
}

UFieldingDeck::UFieldingDeck(const FFieldingDeckDesc& Descriptor)
	: UHGBBDeck(Descriptor)
{
	for (const auto& CardType : Descriptor.CardTypes)
	{
		auto Type = CardType.Key;
		int32 Num = CardType.Value;
		for (int32 CardIndex = 0; CardIndex < Num; ++CardIndex)
		{
			auto Card = NewObject<UFieldingCard>(this, Type);
			Cards.Add(Card);
		}
	}

	Algo::RandomShuffle(Cards);
}
