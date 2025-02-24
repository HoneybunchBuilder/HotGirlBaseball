// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "PlayerPawn.h"
#include "FieldingPawn.generated.h"

UCLASS()
class HOTGIRLBASEBALL_API AFieldingPawn : public APlayerPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFieldingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
