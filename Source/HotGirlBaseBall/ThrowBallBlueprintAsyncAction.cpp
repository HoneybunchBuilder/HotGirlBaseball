// Copyright Ada Tufankjian 2025


#include "ThrowBallBlueprintAsyncAction.h"

void UThrowBallBlueprintAsyncAction::ThrowCompleted()
{
	check(AIController);
	AIController->AIBallThrown.RemoveDynamic(this, &UThrowBallBlueprintAsyncAction::ThrowCompleted);
	Completed.Broadcast();
}

UThrowBallBlueprintAsyncAction* UThrowBallBlueprintAsyncAction::AIThrowBallTo(AFieldingAIController* Controller, const APawn* Target)
{
	auto* Action = NewObject<UThrowBallBlueprintAsyncAction>();
	if (Action)
	{
		Action->AIController = Controller;
		Action->Target = Target;
	}
	return Action;
}

void UThrowBallBlueprintAsyncAction::Activate()
{
	check(AIController);
	check(Target);

	// Issue a throw command and listen for when that is done
	AIController->AIBallThrown.AddDynamic(this, &UThrowBallBlueprintAsyncAction::ThrowCompleted);
	AIController->ThrowBallTo(Target);
}
