// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"

#include "Bat.generated.h"

UCLASS()
class HOTGIRLBASEBALL_API ABat : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ABat();

	//~ Begin IAbilitySystemInterface
	/** Returns our Ability System Component. */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
