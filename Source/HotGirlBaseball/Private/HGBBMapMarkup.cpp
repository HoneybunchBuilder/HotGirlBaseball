// Copyright Ada Tufankjian 2025


#include "HGBBMapMarkup.h"

#include "Components/SplineComponent.h"

#include "HGBBFunctionLibrary.h"
#include "HGBBBaseMarker.h"
#include "HGBBDugout.h"
#include "HGBBBatterBox.h"
#include "HGBBCameraAnchor.h"

AHGBBMapMarkup::AHGBBMapMarkup()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Infield = CreateDefaultSubobject<USplineComponent>(TEXT("Infield"));
	Infield->SetupAttachment(RootComponent);

	Playfield = CreateDefaultSubobject<USplineComponent>(TEXT("Playfield"));
	Playfield->SetupAttachment(RootComponent);

	LeftFoul = CreateDefaultSubobject<USplineComponent>(TEXT("Left Foul Line"));
	LeftFoul->SetupAttachment(RootComponent);

	RightFoul = CreateDefaultSubobject<USplineComponent>(TEXT("Right Foul Line"));
	RightFoul->SetupAttachment(RootComponent);
}

AHGBBBaseMarker* AHGBBMapMarkup::GetMarkerForBase(EBase Base) const
{
	return BaseMarkers[(int32)Base];
}

void AHGBBMapMarkup::RemovePawnFromGuardDuty(const APawn* Pawn)
{
	for (const auto Base : BaseMarkers)
	{
		if (Base->GetGuardingPawn() == Pawn)
		{
			Base->SetGuardingPawn(nullptr);
			return; // No pawn should ever be marked as guarding two bases at the same time so we can early out
		}
	}
}

const TArray<AHGBBCameraAnchor*>& AHGBBMapMarkup::GetCameraAnchors() const
{
	return CameraAnchors;
}

FVector AHGBBMapMarkup::GetBaseLocation(EBase Base) const
{
	return BaseMarkers[(int32)Base]->GetActorLocation();
}

AHGBBDugout* AHGBBMapMarkup::GetDugout(ETeamType Team) const
{
	return Team == ETeamType::Home ? HomeDugout : AwayDugout;
}

AHGBBBatterBox* AHGBBMapMarkup::GetBatterBox(EHandedness Handedness) const
{
	return Handedness == EHandedness::LeftHanded ? BatterBoxLH : BatterBoxRH;
}

bool AHGBBMapMarkup::IsLocationFoul(const FVector& Location) const
{
	/*
		In baseball, the foul boundaries are determined by left and right foul lines

		So we just need some markup that defines these lines and then we just need to 
		check if the given point is left of the left foul line or right of the right foul line.
	*/

	// Assume that the left foul and right foul splines have just two points each
	check(LeftFoul->GetNumberOfSplinePoints() == 2);
	check(RightFoul->GetNumberOfSplinePoints() == 2);

	auto IsPointLeftOf = [](USplineComponent* Spline, FVector2D Point) -> bool {
		// Don't care about height here
		const auto Start = FVector2D(Spline->GetWorldLocationAtSplinePoint(0));
		const auto End = FVector2D(Spline->GetWorldLocationAtSplinePoint(1));
		// https://stackoverflow.com/questions/1560492/how-to-tell-whether-a-point-is-to-the-right-or-left-side-of-a-line
		return FMath::Sign((End.X - Start.X) * (Point.Y - Start.Y) - (End.Y - Start.Y) * (Point.X - Start.X)) < 0;
	};

	const bool LeftOfLeftFoul = IsPointLeftOf(LeftFoul, FVector2D(Location));
	const bool RightOfRightFoul = !IsPointLeftOf(RightFoul, FVector2D(Location));

	return LeftOfLeftFoul || RightOfRightFoul;
}

bool AHGBBMapMarkup::IsLocationHomeRun(const FVector& Location) const
{
	return !UHGBBFunctionLibrary::DoesSplineContainLocation(Playfield, Location) && !IsLocationFoul(Location);
}

void AHGBBMapMarkup::BeginPlay()
{
	Super::BeginPlay();

	// Retrieve base markers and map them to their relevant base enum
	auto Markers = UHGBBFunctionLibrary::GetAllActorsOfClass<AHGBBBaseMarker>(this);
	check(Markers.Num() == NumBases);
	BaseMarkers.SetNum(NumBases);
	for (const auto& BaseMarker : Markers)
	{
		BaseMarkers[int32(BaseMarker->GetBase())] = BaseMarker;
	}

	// Collect and organize all dugouts
	const auto Dugouts = UHGBBFunctionLibrary::GetAllActorsOfClass<AHGBBDugout>(this);
	for (const auto& Dugout : Dugouts)
	{
		const auto DugoutTeamType = Dugout->GetTeamType();
		if (DugoutTeamType == ETeamType::Home)
		{
			HomeDugout = Dugout;
		}
		else if (DugoutTeamType == ETeamType::Away)
		{
			AwayDugout = Dugout;
		}
	}
	
	// Collect and organize all batters boxes
	const auto BatterBoxes = UHGBBFunctionLibrary::GetAllActorsOfClass<AHGBBBatterBox>(this);
	for (const auto& BatterBox : BatterBoxes)
	{
		const auto Handedness = BatterBox->GetHandedness();
		if (Handedness == EHandedness::LeftHanded)
		{
			BatterBoxLH = BatterBox;
		}
		else if (Handedness == EHandedness::RightHanded)
		{
			BatterBoxRH = BatterBox;
		}
	}

	// Collect all camera anchors
	CameraAnchors = UHGBBFunctionLibrary::GetAllActorsOfClass<AHGBBCameraAnchor>(this);
}
