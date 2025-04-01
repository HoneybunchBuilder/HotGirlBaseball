// Copyright Ada Tufankjian 2025


#include "Bat.h"

ABat::ABat()
{

}

void ABat::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent* ABat::GetAbilitySystemComponent() const 
{
	return nullptr;
}

void ABat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

