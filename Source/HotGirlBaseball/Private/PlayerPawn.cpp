// Copyright Ada Tufankjian 2025


#include "PlayerPawn.h"

APlayerPawn::APlayerPawn()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	// Some hand massaged offsets
	Capsule->SetRelativeLocation(FVector(0, 0, 100.0f));
	Capsule->SetCapsuleHalfHeight(100.0f);
	Capsule->SetCapsuleRadius(26);

	HeadMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadMesh"));
	HeadMesh->SetRelativeLocation(FVector(0, 0, -100.0f)); // Just for lining things up
	HeadMesh->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/ModularAnimeCharacter/Meshes/SK_face"))); // We care about sockets relative to this base mesh
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

	// Begin attaching components in hierarchy 

	Capsule->SetupAttachment(RootComponent);

	// HACK: Must give hair pieces a known offset
	// Not sure what's up with this; had to do it in the pure BP based approach too
	const auto HairLocationOffset = FVector(-0.040815f,-8.644101f,3.422167f);
	const auto HairRotationOffset = FRotator(0.000000, 0.000000, -90.000000);

	const FTransform HairOffset(HairRotationOffset, HairLocationOffset);

	HeadMesh->SetupAttachment(Capsule);
	CustomHead->SetupAttachment(HeadMesh);

	HairBackMesh->SetupAttachment(HeadMesh, HairSocketName);
	HairBackMesh->SetRelativeTransform(HairOffset);
	CustomHairBack->SetupAttachment(HairBackMesh);

	HairFringeMesh->SetupAttachment(HeadMesh, HairSocketName);
	HairFringeMesh->SetRelativeTransform(HairOffset);
	CustomHairFringe->SetupAttachment(HairFringeMesh);

	HairSidesShortMesh->SetupAttachment(HeadMesh, HairSocketName);
	HairSidesShortMesh->SetRelativeTransform(HairOffset);
	CustomHairSidesShort->SetupAttachment(HairSidesShortMesh);

	HairSidesLongMesh->SetupAttachment(HeadMesh, HairSocketName);
	HairSidesLongMesh->SetRelativeTransform(HairOffset);
	CustomHairSidesLong->SetupAttachment(HairSidesLongMesh);

	HairPonytailMesh->SetupAttachment(HeadMesh, HairSocketName);
	HairPonytailMesh->SetRelativeTransform(HairOffset);
	CustomHairPonytail->SetupAttachment(HairPonytailMesh);

	HairPigtailsMesh->SetupAttachment(HeadMesh, HairSocketName);
	HairPigtailsMesh->SetRelativeTransform(HairOffset);
	CustomHairPigtails->SetupAttachment(HairPigtailsMesh);

	BodyMesh->SetupAttachment(HeadMesh);
	CustomBody->SetupAttachment(BodyMesh);

	// With this only the Head mesh will need an anim BP supplied
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

	// Set up some less dramatic actor components
	MovementComponent = CreateDefaultSubobject<UHGBBMovement>(TEXT("HGBBMovement"));
	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovementBase"));

	PrimaryActorTick.bCanEverTick = true;

	// Try to apply instance while we're here but this will need to be called by the BP constructor for proper behavior
	ApplyCustomObjectInstance();
}

void APlayerPawn::SetPlayerDisplay(TObjectPtr<UCustomizableObjectInstance> InCustomInstance, FHGBBTeam InTeam)
{
	CustomObject = InCustomInstance;
	Team = InTeam;
	ApplyCustomObjectInstance();
}

void APlayerPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// Another attempt to make sure the custom instance is loaded but BP will probably override this
	ApplyCustomObjectInstance();
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	// Another attempt to make sure the custom instance is loaded but BP will probably override this
	ApplyCustomObjectInstance();
}

void APlayerPawn::ApplyCustomObjectInstance()
{
	if (CustomObject == nullptr) // Not sure when in the init process this can happen but this can be null and that will crash deep in mutable later on
	{
		return;
	}

	for(auto Piece : CustomPieces)
	{
		Piece->SetCustomizableObjectInstance(CustomObject);
	}

	// Apply team colors
	CustomObject->SetColorParameterSelectedOption(TEXT("TeamColor1"), Team.PrimaryColor);
	CustomObject->SetColorParameterSelectedOption(TEXT("TeamColor2"), Team.SecondaryColor);
	CustomObject->SetColorParameterSelectedOption(TEXT("TeamColor3"), Team.TertiaryColor);

	CustomObject->UpdateSkeletalMeshAsync(false, true);
}

void APlayerPawn::TickLockToFloor()
{
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickLockToFloor();
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

