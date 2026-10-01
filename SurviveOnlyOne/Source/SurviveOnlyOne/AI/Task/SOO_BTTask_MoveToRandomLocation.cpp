// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/SOO_BTTask_MoveToRandomLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Pawn.h"

USOO_BTTask_MoveToRandomLocation::USOO_BTTask_MoveToRandomLocation()
{
	NodeName = TEXT("SOO Move To Random Location");
}

EBTNodeResult::Type USOO_BTTask_MoveToRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = AIController ? AIController->GetPawn() : nullptr;

	if (!AIController || !ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(ControlledPawn->GetWorld());
	if (!NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation ResultLocation;
	const bool bFound = NavSystem->GetRandomReachablePointInRadius(ControlledPawn->GetActorLocation(), WanderRadius, ResultLocation);

	if (!bFound)
	{
		return EBTNodeResult::Failed;
	}

	AIController->MoveToLocation(ResultLocation.Location);
	return EBTNodeResult::Succeeded;
}
