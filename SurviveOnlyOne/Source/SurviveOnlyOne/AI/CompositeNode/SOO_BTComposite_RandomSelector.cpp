// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CompositeNode/SOO_BTComposite_RandomSelector.h"

USOO_BTComposite_RandomSelector::USOO_BTComposite_RandomSelector()
{
	NodeName = "SOO Random Selector (Pick One)";
}

int32 USOO_BTComposite_RandomSelector::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	if (PrevChild == BTSpecialChild::NotInitialized)
	{
		return GetChildrenNum() > 0 ? FMath::RandRange(0, GetChildrenNum() - 1) : BTSpecialChild::ReturnToParent;
	}

	return BTSpecialChild::ReturnToParent;
}