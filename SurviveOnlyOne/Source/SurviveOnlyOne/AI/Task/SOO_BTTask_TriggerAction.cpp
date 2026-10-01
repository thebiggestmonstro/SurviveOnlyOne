// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/SOO_BTTask_TriggerAction.h"
#include "Player/Input/SOO_ActionComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"

USOO_BTTask_TriggerAction::USOO_BTTask_TriggerAction()
{
	NodeName = TEXT("SOO Trigger Action");
	bNotifyTick = true;
}

EBTNodeResult::Type USOO_BTTask_TriggerAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FMemory* Memory = reinterpret_cast<FMemory*>(NodeMemory);
	Memory->bActivated = false;
	Memory->RemainingHoldTime = 0.0f;

	APawn* ControlledPawn = OwnerComp.GetAIOwner() ? OwnerComp.GetAIOwner()->GetPawn() : nullptr;
	USOO_ActionComponent* ActionComponent = ControlledPawn ? ControlledPawn->FindComponentByClass<USOO_ActionComponent>() : nullptr;
	if (!ActionComponent)
	{
		return EBTNodeResult::Failed;
	}

	if (!ActionComponent->TryActivateAction(ActionTag))
	{
		return EBTNodeResult::Failed;
	}

	Memory->bActivated = true;

	const bool bIsHoldType = HoldDurationRange.Y > 0.0f;
	if (!bIsHoldType)
	{
		return EBTNodeResult::Succeeded;
	}

	Memory->RemainingHoldTime = FMath::RandRange(HoldDurationRange.X, HoldDurationRange.Y);
	return EBTNodeResult::InProgress;
}

void USOO_BTTask_TriggerAction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FMemory* Memory = reinterpret_cast<FMemory*>(NodeMemory);
	Memory->RemainingHoldTime -= DeltaSeconds;

	if (Memory->RemainingHoldTime <= 0.0f)
	{
		APawn* ControlledPawn = OwnerComp.GetAIOwner() ? OwnerComp.GetAIOwner()->GetPawn() : nullptr;
		if (USOO_ActionComponent* ActionComponent = ControlledPawn ? ControlledPawn->FindComponentByClass<USOO_ActionComponent>() : nullptr)
		{
			ActionComponent->CancelAction(ActionTag);
		}

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

EBTNodeResult::Type USOO_BTTask_TriggerAction::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FMemory* Memory = reinterpret_cast<FMemory*>(NodeMemory);

	if (Memory->bActivated)
	{
		APawn* ControlledPawn = OwnerComp.GetAIOwner() ? OwnerComp.GetAIOwner()->GetPawn() : nullptr;
		if (USOO_ActionComponent* ActionComponent = ControlledPawn ? ControlledPawn->FindComponentByClass<USOO_ActionComponent>() : nullptr)
		{
			ActionComponent->CancelAction(ActionTag);
		}
	}

	return EBTNodeResult::Aborted;
}