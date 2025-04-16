// Copyright Ada Tufankjian 2025


#include "HGBBBall.h"

#include "AbilitySystemComponent.h"

AHGBBBall::AHGBBBall()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	RootComponent = Mesh;

	PitchEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Pitch Effect"));
	PitchEffect->SetupAttachment(Mesh);

	TravelRibbon = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Travel Ribbon"));
	TravelRibbon->SetupAttachment(Mesh);

	HitEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Hit Effect"));
	HitEffect->SetupAttachment(Mesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	AbilityComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability Component"));
}

UAbilitySystemComponent* AHGBBBall::GetAbilitySystemComponent() const
{
	return nullptr;
}

void AHGBBBall::BeginPlay()
{
	Super::BeginPlay();
}

void AHGBBBall::Pitch(float ReleaseAlpha, const FVector& Target)
{
}

void AHGBBBall::Pass(const FVector& Target)
{
}

void AHGBBBall::TryCatchOut2()
{
}

void AHGBBBall::DetermineAndRedirectHit2(float BatTimeToContactPoint)
{
}

void AHGBBBall::HitResultVisLogStart2(float EstTimeToHit)
{
}

void AHGBBBall::ActivateThrowEffect2(float Alpha)
{
}

float AHGBBBall::CalcTimeToTarget2()
{
	return 0.0f;
}

float AHGBBBall::GetProjectileToTargetTime(const FVector& Target, const FVector& LaunchVelocity)
{
	return 0.0f;
}

void AHGBBBall::SetLive(bool bLive)
{
}

void AHGBBBall::SetHit(bool bHit)
{
}

FHitType AHGBBBall::GenerateHit2(const FVector& HitPos)
{
	return FHitType();
}
