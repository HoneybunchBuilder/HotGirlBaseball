// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"

#include "HGBBBat.generated.h"

/**
	The Bat actor for this baseball game
*/
UCLASS(BlueprintType, Blueprintable)
class HOTGIRLBASEBALL_API AHGBBBat : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AHGBBBat();

	/** Returns the cached initial relative transform of the bat mesh so it can be re-applied */
	UFUNCTION(BlueprintCallable)
	const FTransform& GetInitialRelativeTransform() const;

	/** Call when the given actor wants to wield the bat */
	UFUNCTION(BlueprintCallable)
	void BatterWields(USceneComponent* AttachComponent, const FName& Socket);

	/** Call when the given actor wants to release the bat */
	UFUNCTION(BlueprintCallable)
	void BatterReleases();

	//~ Begin IAbilitySystemInterface
	/** Returns our Ability System Component. */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface

protected:
	virtual void BeginPlay() override;

private:
	/** The display mesh */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;

	/** The underlying ability component for driving special gameplay effects */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAbilitySystemComponent> AbilityComponent;

	/**
		We want the relative transform set in BP to be respected even if this actor is attached to some other 
	socket. AttachActorToComponent can nuke this relative transform so we cache it here so it can be re-applied later
	*/
	FTransform InitialRelativeTransform;
};
