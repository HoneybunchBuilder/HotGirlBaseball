// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "MuCO/CustomizableSkeletalComponent.h"

#include "PlayerPawn.generated.h"

UCLASS()
class HOTGIRLBASEBALL_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> Capsule;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> HeadMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCustomizableSkeletalComponent> CustomHead;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> HairBackMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCustomizableSkeletalComponent> CustomHairBack;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> HairFringeMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCustomizableSkeletalComponent> CustomHairFringe;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> HairSidesShortMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCustomizableSkeletalComponent> CustomHairSidesShort;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> HairSidesLongMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCustomizableSkeletalComponent> CustomHairSidesLong;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> HairPonytailMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCustomizableSkeletalComponent> CustomHairPonytail;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> HairPigtailsMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCustomizableSkeletalComponent> CustomHairPigtails;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> BodyMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCustomizableSkeletalComponent> CustomBody;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UCustomizableObjectInstance> CustomObject;

protected:
	// Hair meshes will attach to a socket of this name on the Head mesh
	const FName HairSocketName = FName(TEXT("head"));

	// Helper array of all the customizable components
	TArray<TObjectPtr<UCustomizableSkeletalComponent>> CustomPieces;
	
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	// Must be called by blueprint BeginPlay & Constructor to work properly
	UFUNCTION(BlueprintCallable)
	virtual void ApplyCustomObjectInstance();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
