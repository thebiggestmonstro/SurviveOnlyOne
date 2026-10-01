// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SOO_DecoyAIController.generated.h"

class UBehaviorTree;
class UBlackboardData;

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API ASOO_DecoyAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASOO_DecoyAIController();

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
