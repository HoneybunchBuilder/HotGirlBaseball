// Copyright Ada Tufankjian 2025


#include "HGBBBall.h"

#include "AbilitySystemComponent.h"
#include "MetaSoundsource.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "VisualLogger/VisualLogger.h"

#include "HGBBStrikeZone.h"
#include "HGBBFunctionLibrary.h"
#include "HGBBMapMarkup.h"

AHGBBBall::AHGBBBall()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	Mesh->OnComponentHit.AddDynamic(this, &AHGBBBall::OnCollisionHit);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AHGBBBall::OnBeginOverlap);
	RootComponent = Mesh;

	PitchEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Pitch Effect"));
	PitchEffect->bAutoActivate = false;
	PitchEffect->SetupAttachment(Mesh);

	TravelRibbon = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Travel Ribbon"));
	TravelRibbon->SetVisibility(false);
	TravelRibbon->SetupAttachment(Mesh);

	HitEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Hit Effect"));
	HitEffect->bAutoActivate = false;
	HitEffect->SetupAttachment(Mesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->bShouldBounce = true;

	AbilityComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability Component"));
}

UAbilitySystemComponent* AHGBBBall::GetAbilitySystemComponent() const
{
	return AbilityComponent;
}

void AHGBBBall::BeginPlay()
{
	Super::BeginPlay();

	StrikeZone = UHGBBFunctionLibrary::GetActorOfClass<AHGBBStrikeZone>(this);
	check(StrikeZone);

	MapMarkup = UHGBBFunctionLibrary::GetActorOfClass<AHGBBMapMarkup>(this);
	check(MapMarkup);
}

bool AHGBBBall::GetLive() const
{
	return bLive;
}

bool AHGBBBall::GetHit() const
{
	return bHit;
}

bool AHGBBBall::GetShouldHit() const
{
	return bShouldHit;
}

FHitType AHGBBBall::GetHitType() const
{
	return HitType;
}

bool AHGBBBall::GetStrike() const
{
	return bStrike;
}

bool AHGBBBall::GetHitLanded() const
{
	return bHitLanded;
}

FVector AHGBBBall::GetHitLandingLocation() const
{
	return HitLandingLocation;
}

FVector AHGBBBall::GetVelocity() const
{
	if (ProjectileMovement)
	{
		return ProjectileMovement->Velocity;
	}
	return FVector::ZeroVector;
}

void AHGBBBall::FinishPlay()
{
	// Hide the travel ribbon while the ball is not live
	TravelRibbon->SetVisibility(false);

	// Don't want the ball moving anymore
	ProjectileMovement->SetActive(false);

	// Notify listeners that the play is over
	PlayFinished.Broadcast();

	// Reset these here so that they can be inspected by anything that listened to PlayFinished
	bCanCatchOut = false;
	bLive = false;
	bShouldHit = false;
	bStrike = false;
	bHitLanded = false;
	HitType = {};
}

void AHGBBBall::Pitch(float ReleaseAlpha, const FVector& Target)
{
	// Set the current known state of the ball
	bShouldHit = false;
	bStrike = false;
	bCanCatchOut = false;
	bInAir = true;
	bHit = false;
	bLive = true;
	HitType = {};

	// Activate the particle effect for the pitch
	ActivateThrowEffect2(ReleaseAlpha);

	// TODO: Launch speed should be determined by player stats and game state
	ThrowBallToLocation(Target, 2000.0f);
}

void AHGBBBall::Pass(const FVector& Target)
{
	bInAir = true;

	// TODO: Launch speed should be determined by player stats and game state
	ThrowBallToLocation(Target, 5000.0f);

	UE_VLOG_LOCATION(this, LogTemp, Verbose, Target, 10, FColor::Yellow, TEXT("Pass Target"));
	UE_VLOG_ARROW(this, LogTemp, Verbose, GetActorLocation(), Target, FColor::Yellow, TEXT("Pass Target"));
}

void AHGBBBall::FielderCatches(USceneComponent* AttachComponent, const FName& Socket)
{
	bInAir = false; // Not in the air if a fielder has caught the ball

	// See if we are catching a runner out
	if (bCanCatchOut && !bHitLanded)
	{
		bCanCatchOut = false;
		HitCaught.Broadcast();
	}

	// Given socket must exist
	check(AttachComponent->DoesSocketExist(Socket));

	// Teleport the ball to the desired location first (Forget why we needed to do this tbh)
	SetActorLocation(AttachComponent->GetSocketLocation(Socket), false, nullptr, ETeleportType::TeleportPhysics);

	// Attach the ball to the given attachment
	AttachToComponent(AttachComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);

	// Make sure the mesh isn't offset all
	Mesh->SetRelativeLocation(FVector::ZeroVector);

	// Disable projectile movement so we don't move any more
	ProjectileMovement->SetActive(false);
}

void AHGBBBall::DetermineAndRedirectHit2(float BatTimeToContactPoint)
{
	if (!bLive)
	{
		return;
	}
	
	const auto HitCapsule = StrikeZone->GetHitCapsule();
	const FVector CapsulePos = HitCapsule->GetComponentLocation();


	UE_VLOG_SPHERE(this, LogTemp, Verbose, GetActorLocation(), 5.0f, FColor::Cyan, TEXT("Ball Resolve Start Pos"));
#if ENABLE_VISUAL_LOG
	{
		const FVector Start = CapsulePos + FVector(0, HitCapsule->GetScaledCapsuleHalfHeight(), 0);
		const FVector End = CapsulePos - FVector(0, HitCapsule->GetScaledCapsuleHalfHeight(), 0);
		const float Radius = HitCapsule->GetScaledCapsuleRadius();
		UE_VLOG_CYLINDER(this, LogTemp, Verbose, Start, End, Radius, FColor::Cyan, TEXT("Hit Capsule"));
	}
#endif
	UE_VLOG_SPHERE(this, LogTemp, Verbose, ThrowTarget, 5.0f, FColor::Blue, TEXT("Throw Target"));


	check(bShouldHit == false); // Hit should not already be determined

	// Calculate possible redirection target
	FVector NewTarget = {};
	const float DistToClosestPointOnCapsule = HitCapsule->GetDistanceToCollision(GetActorLocation(), NewTarget);
	check(DistToClosestPointOnCapsule >= 0.0f); // Not expecting a negative value

	UE_VLOG_SPHERE(this, LogTemp, Verbose, NewTarget, 5.0f, FColor::Red, TEXT("New Target"));

	const FVector TargetDelta = NewTarget - ThrowTarget;
	const float TargetDeltaDifference = TargetDelta.Length();

	// Bail if redirecting the ball would cause too large a change in trajectory
	if (TargetDeltaDifference > 50.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed Distance Test: %f"), TargetDeltaDifference);
		return;
	}

	// Make sure if we were to redirect the ball, that the timing would still be within reason
	const float TimeToNewTarget = UHGBBFunctionLibrary::TimeProjectileToTarget(GetActorLocation(), NewTarget, ProjectileMovement->Velocity, ProjectileMovement->GetGravityZ());

	// If the time isn't within the redirection threshold, we need to stop
	if (!UHGBBFunctionLibrary::IsFloatInRange(TimeToNewTarget, TimeToNewTarget - RedirectTimingThreshold, TimeToNewTarget + RedirectTimingThreshold, true, true))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed Timing Test: %f %f %f"), TimeToTarget, TimeToNewTarget, RedirectTimingThreshold);
		return;
	}

	// The ball *should* connect now
	bShouldHit = true;

	// Based on how much time is left in the flight to the target, recalculate a new velocity for the ball
	const float LaunchSpeed = [this, TimeToNewTarget]() -> float {
		const float OriginalTimeRemaining = TimeToTarget - (UGameplayStatics::GetRealTimeSeconds(this) - TimeThrown);
		const float DiffTimeRemaining = TimeToNewTarget - OriginalTimeRemaining;

		// What percentage of the current velocity do we need to make it to the new target
		const float TimeRemainingAlpha = DiffTimeRemaining / TimeToNewTarget;

		const FVector VelocityOffset = ProjectileMovement->Velocity * TimeRemainingAlpha;
		const FVector NewLaunchVelocity = ProjectileMovement->Velocity + VelocityOffset;
		return NewLaunchVelocity.Length();
	}();

	auto ProjectileParams = UGameplayStatics::FSuggestProjectileVelocityParameters(this, GetActorLocation(), NewTarget, LaunchSpeed);
	ProjectileParams.CollisionRadius = Mesh->GetStaticMesh()->GetBounds().BoxExtent.Length(); // Derive collision radius from mesh bounds
	ProjectileParams.TraceOption = ESuggestProjVelocityTraceOption::DoNotTrace;

	FVector NewVelocity = {};
	UGameplayStatics::SuggestProjectileVelocity(ProjectileParams, NewVelocity);

	UE_LOG(LogTemp, Warning, TEXT("Redirecting Ball"));
	ProjectileMovement->Velocity = NewVelocity;
	UE_LOG(LogTemp, Warning, TEXT("Ball Velocity: %s"), *ProjectileMovement->Velocity.ToString());

	UE_VLOG_SPHERE(this, LogTemp, Verbose, NewTarget, 5.0f, FColor::Cyan, TEXT("Redirected Target"));
	UE_VLOG_ARROW(this, LogTemp, Verbose, GetActorLocation(), GetActorLocation() + NewVelocity, FColor::Blue, TEXT("Redirected Velocity"));
}

void AHGBBBall::ThrowBallToLocation(const FVector& Target, float LaunchSpeed)
{
	Mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	const FVector Start = GetActorLocation();
	auto ProjectileParams = UGameplayStatics::FSuggestProjectileVelocityParameters(this, Start, Target, LaunchSpeed);
	ProjectileParams.CollisionRadius = Mesh->GetStaticMesh()->GetBounds().BoxExtent.Length(); // Derive collision radius from mesh bounds
	ProjectileParams.TraceOption = ESuggestProjVelocityTraceOption::DoNotTrace;

	// Determine the launch velocity of the ball
	if (!UGameplayStatics::SuggestProjectileVelocity(ProjectileParams, LaunchVelocity))
	{
		check(false);
		return;
	}
	ThrowTarget = Target;
	TimeThrown = UGameplayStatics::GetRealTimeSeconds(this);
	TimeToTarget = UHGBBFunctionLibrary::TimeProjectileToTarget(Start, ThrowTarget, LaunchVelocity, ProjectileMovement->GetGravityZ());

	ProjectileMovement->Velocity = LaunchVelocity;
	ProjectileMovement->SetUpdatedComponent(RootComponent); // Required for the projectile movement to launched multiple times
	ProjectileMovement->SetActive(true);
	UE_LOG(LogTemp, Warning, TEXT("Ball Velocity: %s"), *ProjectileMovement->Velocity.ToString());

	// Play Sound effect
	UGameplayStatics::PlaySoundAtLocation(this, ThrownSoundSource, Start);
}

void AHGBBBall::OnCollisionHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Don't actually care what we hit
	(void)HitComp;
	(void)OtherActor;
	(void)OtherComp;
	(void)NormalImpulse;
	(void)Hit;

	// Nothing to do if ball isn't already live
	if (!bLive)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ball Ignoring Collision: Not Live"));
		return;
	}

	if (bHit)
	{
		if (HitType.Direction == EHitDirection::Foul)
		{
			// Foul balls need to be marked as landed here
			// Play will be finished up later
			UE_LOG(LogTemp, Warning, TEXT("Ball Collision: Foul Ball"));
			if (OtherActor != StrikeZone)
			{
				bHitLanded = true;
			}
		}
		else
		{
			if (bHitLanded)
			{
				UE_LOG(LogTemp, Warning, TEXT("Ball Collision: Hit Ground"));
				BallHitsGround.Broadcast();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Ball Collision: Hit Landed"));
				bHitLanded = true;
				HitLands.Broadcast();
			}
		}
	}
	else
	{
		// The batter missed and the catcher didn't intercept so we probably hit a wall or something
		// TODO: Do we care about the catcher missing? In real baseball a runner could steal a base
		UE_LOG(LogTemp, Warning, TEXT("Ball Resetting On Hit"));
		FinishPlay();
	}
}

void AHGBBBall::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	(void)OverlappedComp;
	(void)OtherBodyIndex;
	(void)bFromSweep;

	// Nothing to do if ball isn't already live
	if (!bLive)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ball Ignoring Overlap: Not Live"));
		return;
	}

	// Only care about interactions with the strike zone
	if (Cast<AHGBBStrikeZone>(Other) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ball Ignoring Overlap: Not Strike Zone"));
		return;
	}

	// If the ball is already considered hit, we can also ignore this
	if (bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ball Ignoring Overlap: Already Hit"));
		return;
	}

	check(StrikeZone);
	if (OtherComp == StrikeZone->GetHitBox())
	{
		// If we overlap the strike zone, this ball should be marked as a strike
		// It can still be hit but we want to record that the pitch, overall, was a strike
		bStrike = true;
		UE_LOG(LogTemp, Warning, TEXT("Ball Overlap: Strike"));
		return;
	}

	// If we encountered anything other than the strike zone hit capsule we can bail
	if (OtherComp != StrikeZone->GetHitCapsule())
	{
		UE_LOG(LogTemp, Warning, TEXT("Ball Ignoring Overlap: Not Hit Capsule"));
		return;
	}
	
	// If we already determined that the ball shouldn't register a hit (e.g. because the swing was too early or too late) we can bail
	if (!bShouldHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ball Ignoring Overlap: Shouldn't Hit"));
		return;
	}

	// We're registering a hit! Play a sound to accompany this
	UGameplayStatics::PlaySoundAtLocation(this, HitSoundSource, Mesh->GetComponentLocation());

	UE_LOG(LogTemp, Warning, TEXT("Generating hit!"));
	GenerateHit(SweepResult.ImpactPoint);

	bHit = true;
	bCanCatchOut = true;

	HitEffect->Activate(); // Play hit particle effect!

	// If the hit was a home run, start a timer to finish the play after a given amount of time
	if (HitType.Direction == EHitDirection::HomeRun)
	{
		UE_LOG(LogTemp, Warning, TEXT("Home Run!"));
		HomeRun.Broadcast();
		// TODO: We want a bit more fanfare for a home run
		FTimerHandle Handle = {};
		GetWorldTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([this]() {
			FinishPlay();
		}), 3.0f, false);
		return;
	}

	// If the hit was a foul, start a timer to finish the play after a small amount of time
	if (HitType.Direction == EHitDirection::Foul)
	{
		UE_LOG(LogTemp, Warning, TEXT("Foul Ball!"));
		FoulBall.Broadcast();
		FTimerHandle Handle = {};
		GetWorldTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([this]() {
			FinishPlay();
		}), 1.5f, false);
		return;
	}

	// If this wasn't a home run or a foul we can just report the hit
	UE_LOG(LogTemp, Warning, TEXT("Broadcasting hit!"));
	PlayStateChanged.Broadcast(bHit);
}

void AHGBBBall::ActivateThrowEffect2(float Alpha)
{
	// TODO: We probably want to do more here. Different particles for different effects on pitches, etc.
	const FLinearColor Color = FMath::Lerp(FLinearColor::Red, FLinearColor::Green, Alpha);

	PitchEffect->SetVariableLinearColor(FName(TEXT("FeedbackColor")), Color);
	PitchEffect->SetVisibility(true);
	PitchEffect->Activate();

	TravelRibbon->SetVisibility(true);
}

void AHGBBBall::GenerateHit(const FVector& HitPos)
{
	const float HorizontalHitAlpha = [this]() -> float {
		if (DebugHitOverride)
		{
			return DebugHorizontalAlpha;
		}
		return FMath::RandRange(-1.0f, 1.0f);
	}();
	DebugHorizontalAlpha = HorizontalHitAlpha;

	const float VerticalHitAlpha = [this]() -> float {
		if (DebugHitOverride)
		{
			return DebugVerticalAlpha;
		}
		return FMath::RandRange(-0.25f, 1.0f);
	}();
	DebugVerticalAlpha = VerticalHitAlpha;

	const float HitPower = [this]() -> float {
		if (DebugHitOverride)
		{
			return DebugHitPower;
		}
		return FMath::RandRange(500.0f, 4000.0f);
	}();
	DebugHitPower = HitPower;

	// Calculate hit velocity
	ProjectileMovement->Velocity = [this, HorizontalHitAlpha, VerticalHitAlpha, HitPower]() -> FVector {
		const FVector Forward = FVector::ForwardVector;
		
		const auto VerticalDeg = FMath::GetMappedRangeValueClamped(FVector2D(-.25f, 1.0f), FVector2D(15.0, -100.0), VerticalHitAlpha);
		const auto HorizontalDeg = FMath::GetMappedRangeValueClamped(FVector2D(-1.0f, 1.0f), FVector2D(-65.f, 65.f), HorizontalHitAlpha);

		FVector Velocity = Forward.RotateAngleAxis(VerticalDeg, FVector::RightVector);
		Velocity = Velocity.RotateAngleAxis(HorizontalDeg, FVector::UpVector);

		Velocity.Normalize();
		Velocity *= HitPower;

		return Velocity;
	}();
	UE_LOG(LogTemp, Warning, TEXT("Ball Velocity: %s"), *ProjectileMovement->Velocity.ToString());

	UE_VLOG_SPHERE(this, LogTemp, Verbose, HitPos, 3.0f, FColor::Purple, TEXT("Hit Location"));
	UE_VLOG_ARROW(this, LogTemp, Verbose, HitPos, HitPos + ProjectileMovement->Velocity, FColor::Purple, TEXT("Hit Velocity"));

	FPredictProjectilePathParams PredictParams = {};
	PredictParams.StartLocation = HitPos;
	PredictParams.LaunchVelocity = ProjectileMovement->Velocity;
	PredictParams.bTraceWithChannel = true;
	PredictParams.bTraceComplex = true;
	PredictParams.TraceChannel = ECollisionChannel::ECC_WorldStatic;
	PredictParams.ActorsToIgnore.Add(this);
	PredictParams.OverrideGravityZ = ProjectileMovement->GetGravityZ();
	FPredictProjectilePathResult PredictResult = {};
	if (!UGameplayStatics::PredictProjectilePath(this, PredictParams, PredictResult))
	{
		// If we fail, we have problems
		//check(false);
	}

	HitLandingLocation = PredictResult.LastTraceDestination.Location;
	UE_VLOG_SPHERE(this, LogTemp, Verbose, HitLandingLocation, 25.0f, FColor::Purple, TEXT("Predicted Land"));
	
	EHitArc Arc = EHitArc::PopFly;
	EHitDirection Direction = EHitDirection::Center;

	if (MapMarkup->IsLocationFoul(HitLandingLocation))
	{
		Direction = EHitDirection::Foul;
	}
	else if(MapMarkup->IsLocationHomeRun(HitLandingLocation))
	{
		Direction = EHitDirection::HomeRun;
	}
	else
	{
		if (HorizontalHitAlpha < -CenterFieldThreshold)
		{
			Direction = EHitDirection::Left;
		}
		else if(HorizontalHitAlpha > CenterFieldThreshold)
		{
			Direction = EHitDirection::Right;
		}
	}

	if (VerticalHitAlpha <= GroundBallThreshold)
	{
		Arc = EHitArc::GroundBall;
	}
	else if(VerticalHitAlpha <= LineDriveThreshold)
	{
		Arc = EHitArc::LineDrive;
	}

	HitType = {
		.Arc = Arc,
		.Direction = Direction,
	};
}
