// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SOO_BTTask_MoveToRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API USOO_BTTask_MoveToRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USOO_BTTask_MoveToRandomLocation();

	UPROPERTY(EditAnywhere, Category = "AI")
	float WanderRadius = 1500.0f;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
