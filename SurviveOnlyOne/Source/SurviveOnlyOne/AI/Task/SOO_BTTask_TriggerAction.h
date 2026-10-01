// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameplayTagContainer.h"
#include "SOO_BTTask_TriggerAction.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API USOO_BTTask_TriggerAction : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USOO_BTTask_TriggerAction();

	UPROPERTY(EditAnywhere, Category = "Action")
	FGameplayTag ActionTag;

	UPROPERTY(EditAnywhere, Category = "Action")
	FVector2D HoldDurationRange = FVector2D(0.0f, 0.0f);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	struct FMemory
	{
		float RemainingHoldTime = 0.0f;
		bool bActivated = false;
	};

	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FMemory); }
};
