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
	APlayerPawn(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCapsuleComponent> Capsule;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> HeadMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCustomizableSkeletalComponent> CustomHead;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> HairBackMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCustomizableSkeletalComponent> CustomHairBack;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> HairFringeMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCustomizableSkeletalComponent> CustomHairFringe;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> HairSidesShortMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCustomizableSkeletalComponent> CustomHairSidesShort;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> HairSidesLongMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCustomizableSkeletalComponent> CustomHairSidesLong;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> HairPonytailMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCustomizableSkeletalComponent> CustomHairPonytail;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> HairPigtailsMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCustomizableSkeletalComponent> CustomHairPigtails;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> BodyMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCustomizableSkeletalComponent> CustomBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCustomizableObjectInstance> CustomObject;

protected:
	const FName HairSocketName = FName(TEXT("head"));

	TArray<TObjectPtr<UCustomizableSkeletalComponent>> CustomPieces;
	
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void ApplyCustomObjectInstance();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
