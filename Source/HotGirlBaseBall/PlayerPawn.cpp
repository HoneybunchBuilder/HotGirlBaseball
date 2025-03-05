// Copyright Ada Tufankjian 2025


#include "PlayerPawn.h"

/*
	Current problems:
	Can't seem to get hair to attach properly. When attaching to a socket in blueprint the object is moved to the socket position
*/

APlayerPawn::APlayerPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetCapsuleHalfHeight(100.0f);
	Capsule->SetCapsuleRadius(26);

	HeadMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadMesh"));
	HeadMesh->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/ModularAnimeCharacter/Meshes/SK_face"))); // We need this default to be able to reference sockets
	CustomHead = CreateDefaultSubobject<UCustomizableSkeletalComponent>(TEXT("CustomHead"));

	HairBackMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairBack"));
	CustomHairBack = CreateDefaultSubobject<UCustomizableSkeletalComponent>(TEXT("CustomHairBack"));

	HairFringeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairFringe"));
	CustomHairFringe = CreateDefaultSubobject<UCustomizableSkeletalComponent>(TEXT("CustomHairFringe"));

	HairSidesShortMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairSidesShort"));
	CustomHairSidesShort = CreateDefaultSubobject<UCustomizableSkeletalComponent>(TEXT("CustomHairSidesShort"));

	HairSidesLongMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairSidesLong"));
	CustomHairSidesLong = CreateDefaultSubobject<UCustomizableSkeletalComponent>(TEXT("CustomHairSidesLong"));

	HairPonytailMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairPonytail"));
	CustomHairPonytail = CreateDefaultSubobject<UCustomizableSkeletalComponent>(TEXT("CustomHairPonytail"));

	HairPigtailsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairPigtails"));
	CustomHairPigtails = CreateDefaultSubobject<UCustomizableSkeletalComponent>(TEXT("CustomHairPigtails"));

	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
	CustomBody = CreateDefaultSubobject<UCustomizableSkeletalComponent>(TEXT("CustomBody"));

	Capsule->SetupAttachment(RootComponent);

	HeadMesh->SetupAttachment(Capsule);
	CustomHead->SetupAttachment(HeadMesh);

	HairBackMesh->SetupAttachment(HeadMesh, HairSocketName);
	CustomHairBack->SetupAttachment(HairBackMesh);

	HairFringeMesh->SetupAttachment(HeadMesh, HairSocketName);
	CustomHairFringe->SetupAttachment(HairFringeMesh);

	HairSidesShortMesh->SetupAttachment(HeadMesh, HairSocketName);
	CustomHairSidesShort->SetupAttachment(HairSidesShortMesh);

	HairSidesLongMesh->SetupAttachment(HeadMesh, HairSocketName);
	CustomHairSidesLong->SetupAttachment(HairSidesLongMesh);

	HairPonytailMesh->SetupAttachment(HeadMesh, HairSocketName);
	CustomHairPonytail->SetupAttachment(HairPonytailMesh);

	HairPigtailsMesh->SetupAttachment(HeadMesh, HairSocketName);
	CustomHairPigtails->SetupAttachment(HairPigtailsMesh);

	BodyMesh->SetupAttachment(HeadMesh);
	CustomBody->SetupAttachment(BodyMesh);

	BodyMesh->SetLeaderPoseComponent(HeadMesh);

	CustomHead->SetComponentName("Head");
	CustomHairBack->SetComponentName("HairBack");
	CustomHairFringe->SetComponentName("HairFringe");
	CustomHairSidesShort->SetComponentName("HairSidesShort");
	CustomHairSidesLong->SetComponentName("HairSidesLong");
	CustomHairPonytail->SetComponentName("HairPonytail");
	CustomHairPigtails->SetComponentName("HairPigtails");
	CustomBody->SetComponentName("Body");

	CustomPieces.Add(CustomHead);
	CustomPieces.Add(CustomHairBack);
	CustomPieces.Add(CustomHairFringe);
	CustomPieces.Add(CustomHairSidesShort);
	CustomPieces.Add(CustomHairSidesLong);
	CustomPieces.Add(CustomHairPonytail);
	CustomPieces.Add(CustomHairPigtails);
	CustomPieces.Add(CustomBody);

	PrimaryActorTick.bCanEverTick = true;
}

void APlayerPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ApplyCustomObjectInstance();
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPawn::ApplyCustomObjectInstance()
{
	for(auto Piece : CustomPieces)
	{
		Piece->SetCustomizableObjectInstance(CustomObject);
	}
	CustomObject->UpdateSkeletalMeshAsync(false, true);
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

