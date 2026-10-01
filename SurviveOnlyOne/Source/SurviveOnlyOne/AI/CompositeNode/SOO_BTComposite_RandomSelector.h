// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "SOO_BTComposite_RandomSelector.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API USOO_BTComposite_RandomSelector : public UBTCompositeNode
{
	GENERATED_BODY()
	
public:
	USOO_BTComposite_RandomSelector();

protected:
	virtual int32 GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const override;
};
