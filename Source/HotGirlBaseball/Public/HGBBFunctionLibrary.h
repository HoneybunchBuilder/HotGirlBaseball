// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Widget.h"
#include "HGBBTypes.h"
#include "HGBBDeck.h"

class USplineComponent;

#include "HGBBFunctionLibrary.generated.h"

/**
 * A helper function library for Hot Girl Baseball
 */
UCLASS()
class HOTGIRLBASEBALL_API UHGBBFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** A templated version of GetActorOfClass */
	template<class TActor>
	static TActor* GetActorOfClass(const UObject* WorldContextObject)
	{
		auto Actor = Cast<TActor>(UGameplayStatics::GetActorOfClass(WorldContextObject, TActor::StaticClass()));
		return Actor;
	}

	/** A templated version of GetAllActorOfClass */
	template<class TActor>
	static TArray<TActor*> GetAllActorsOfClass(const UObject* WorldContextObject)
	{
		TArray<AActor*> FoundActors = {};
		UGameplayStatics::GetAllActorsOfClass(WorldContextObject, TActor::StaticClass(), FoundActors);

		TArray<TActor*> TypedActors = {};
		TypedActors.Reserve(FoundActors.Num());
		for (const auto& Actor : FoundActors)
		{
			auto TypedActor = Cast<TActor>(Actor);
			check(TypedActor);
			TypedActors.Add(TypedActor);
		}
		return TypedActors;
	}

	/** Returns true if the given location falls inside the area described by the given spline */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool DoesSplineContainLocation(const USplineComponent* Spline, const FVector& Location);

	/** An adjusted, more C++ convenient version of UKismetMathLibrary::InRange_FloatFloat */
	static bool IsFloatInRange(float Value, float Min, float Max, bool InclusiveMin, bool InclusiveMax);

	/** Get the currently focused widget */
	UFUNCTION(BlueprintCallable)
	static UWidget* GetFocusedWidget();

	/** Return the amount of time in seconds it will take for a projectile to travel from start to end given velocity and gravity */
	UFUNCTION(BlueprintCallable)
	static double TimeProjectileToTarget(const FVector& Start, const FVector& End, const FVector& Velocity, float Gravity);

	/** Look up if the given position is currently responsible for the current base */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool DoesPositionGuardBase(EFieldingPosition Position, EBase Base);

	/** Get priority order from base */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static int32 GetBasePriority(EBase Base);

	/** Get base from priority order */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static EBase GetBaseFromPriority(int32 Priority);
};
