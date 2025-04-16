// Copyright Ada Tufankjian 2025


#include "HGBBBat.h"

#include "AbilitySystemComponent.h"

AHGBBBat::AHGBBBat()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bat Mesh"));
	Mesh->SetupAttachment(RootComponent);

	AbilityComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability Component"));
}

const FTransform& AHGBBBat::GetInitialRelativeTransform() const
{
	return InitialRelativeTransform;
}

void AHGBBBat::BatterWields(USceneComponent* AttachComponent, const FName& Socket)
{
	// Disable physics
	Mesh->SetSimulatePhysics(false);

	// Calling SetSimulatePhysics to true in `BatterReleases` detaches the mesh from the actor's root component,
	// so we have to re-attach it
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// And we re-apply the initial transform for good measure
	Mesh->SetRelativeTransform(InitialRelativeTransform);

	// We need this socket to exist
	check(AttachComponent->DoesSocketExist(Socket));

	// Now we can attach this actor to the given component
	AttachToComponent(AttachComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
}

void AHGBBBat::BatterReleases()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Mesh->SetSimulatePhysics(true);
	// TODO: Apply some starting velocity to avoid jank collisions?
}

UAbilitySystemComponent* AHGBBBat::GetAbilitySystemComponent() const 
{
	return AbilityComponent;
}

void AHGBBBat::BeginPlay()
{
	Super::BeginPlay();
	InitialRelativeTransform = Mesh->GetRelativeTransform();
}
