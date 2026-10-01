// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SOO_DecoyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ASOO_DecoyAIController::ASOO_DecoyAIController()
{
}

void ASOO_DecoyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!BehaviorTreeAsset)
	{
		return;
	}

	RunBehaviorTree(BehaviorTreeAsset);
}