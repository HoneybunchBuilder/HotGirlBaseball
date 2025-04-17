// Copyright Ada Tufankjian 2025


#include "HGBBFunctionLibrary.h"

#include "Components/SplineComponent.h"

bool UHGBBFunctionLibrary::DoesSplineContainLocation(const USplineComponent* Spline, const FVector& Location)
{
	check(Spline);
	const FVector ClosestToSpline = Spline->FindLocationClosestToWorldLocation(Location, ESplineCoordinateSpace::World);

	const auto DiffToClosest = FVector2D(Location - ClosestToSpline).GetSafeNormal();
	// HACK: We have to manually find the appropriate right vector
	const auto Right = [Spline, Location, ClosestToSpline]() -> FVector2D {
		const auto ClosestInputKey = Spline->FindInputKeyClosestToWorldLocation(Location);
		const auto NextLocation = Spline->GetLocationAtSplineInputKey(ClosestInputKey + 0.1, ESplineCoordinateSpace::World);

		const auto DirToNextLoc = (NextLocation - ClosestToSpline).GetSafeNormal();
		const auto Right = FVector2D(FVector::CrossProduct(FVector::UpVector, DirToNextLoc));

		return Right.GetSafeNormal();
	}();

	const auto Dot = FVector2D::DotProduct(DiffToClosest, Right);
	return Dot >= 0.0f;
}

bool UHGBBFunctionLibrary::IsFloatInRange(float Value, float Min, float Max, bool InclusiveMin, bool InclusiveMax)
{
	return ((InclusiveMin ? (Value >= Min) : (Value > Min)) && (InclusiveMax ? (Value <= Max) : (Value < Max)));
}

UWidget* UHGBBFunctionLibrary::GetFocusedWidget()
{
	// See https://georgy.dev/posts/get-focused-widget/

	TSharedPtr<SWidget> FocusedSlateWidget = FSlateApplication::Get().GetUserFocusedWidget(0);
	if (!FocusedSlateWidget.IsValid())
	{
		return nullptr;
	}
	for (TObjectIterator<UWidget> Itr; Itr; ++Itr)
	{
		UWidget* CandidateUMGWidget = *Itr;
		if (CandidateUMGWidget->GetCachedWidget() == FocusedSlateWidget)
		{
			return CandidateUMGWidget;
		}
	}

	return nullptr;
}

double UHGBBFunctionLibrary::TimeProjectileToTarget(const FVector& Start, const FVector& End, const FVector& Velocity, float Gravity)
{
	// Need to solve a quadratic
	// xa = (-b + sqrt(sq(b) - 4ac)) / 2a
	// xb = (-b - sqrt(sq(b) - 4ac)) / 2a

	const float QuadB = Velocity.Z;
	const float QuadC = Start.Z - End.Z;
	const float Quad2A = Gravity; // Gravity is expected to be in regular Unreal units (Centimeters)

	const float QuadBSq = FMath::Square(QuadB);
	const float Quad4AC = 2 * Quad2A * QuadC;

	const float Time = (-QuadB + FMath::Sqrt(QuadBSq - Quad4AC)) / Quad2A;
	return Time;
}

bool UHGBBFunctionLibrary::DoesPositionGuardBase(EFieldingPosition Position, EBase Base)
{
	// Some roles currently don't have any responsbility to guard a base
	// We probably want this to be more dynamic; i.e. if first base is out of commission due to some ability the right fielder could cover
	// Also consider short stop covering second or third depending on the play

	if (Position == EFieldingPosition::FirstBase && Base == EBase::First)
	{
		return true;
	}
	if (Position == EFieldingPosition::SecondBase && Base == EBase::Second)
	{
		return true;
	}
	if (Position == EFieldingPosition::ThirdBase && Base == EBase::Third)
	{
		return true;
	}

	return false;
}

int32 UHGBBFunctionLibrary::GetBasePriority(EBase Base)
{
	switch (Base)
	{
	case EBase::First:
		return 0;
	case EBase::Second:
		return 1;
	case EBase::Third:
		return 2;
	default:
	case EBase::Home:
		return 3;
	}
}

EBase UHGBBFunctionLibrary::GetBaseFromPriority(int32 Priority)
{
	switch (Priority)
	{
	case 0:
		return EBase::First;
	case 1:
		return EBase::Second;
	case 2:
		return EBase::Third;
	case 3:
	default:
		return EBase::Home;
	}
}
