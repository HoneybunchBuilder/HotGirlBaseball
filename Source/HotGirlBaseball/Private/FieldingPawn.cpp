// Copyright Ada Tufankjian 2025


#include "FieldingPawn.h"

// Sets default values
AFieldingPawn::AFieldingPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFieldingPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFieldingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFieldingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

