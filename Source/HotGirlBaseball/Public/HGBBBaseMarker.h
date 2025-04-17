// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FieldingPawn.h"
#include "HGBBBaseMarker.generated.h"

/**
	An actor that marks up a base that can be guarded by a fielder and must be reached by a runner as they round the field
*/
UCLASS(BlueprintType, Blueprintable)
class HOTGIRLBASEBALL_API AHGBBBaseMarker : public AActor
{
	GENERATED_BODY()
	
public:
	AHGBBBaseMarker();

	UFUNCTION(BlueprintCallable)
	EBase GetBase() const;

	/** Specify which pawn is guarding this base. Provide nullptr to specify no pawn guards this base */
	UFUNCTION(BlueprintCallable)
	void SetGuardingPawn(AFieldingPawn* Pawn);

	/** Get whether or not a pawn is currently guarding this base */
	UFUNCTION(BlueprintCallable)
	bool IsGuarded() const;

private:
	/** Enum type specifying which base this marker references */
	UPROPERTY(EditInstanceOnly)
	EBase Base;

	/** A pawn that might be guarding this base */
	TWeakObjectPtr<AFieldingPawn> GuardingPawn;
};
