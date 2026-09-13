// SOO_ActionComponent.cpp

#include "SOO_ActionComponent.h"
#include "Action/SOO_PlayerActionBase.h"
#include "GameFramework/Pawn.h"

USOO_ActionComponent::USOO_ActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USOO_ActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (const TSubclassOf<USOO_PlayerActionBase>& ActionClass : GrantedActionClasses)
	{
		if (!ActionClass)
		{
			continue;
		}

		USOO_PlayerActionBase* NewAction = NewObject<USOO_PlayerActionBase>(this, ActionClass);
		if (NewAction && NewAction->ActionTag.IsValid())
		{
			ActionMap.Add(NewAction->ActionTag, NewAction);
		}
	}
}

bool USOO_ActionComponent::TryActivateAction(FGameplayTag ActionTag)
{
	TObjectPtr<USOO_PlayerActionBase>* FoundAction = ActionMap.Find(ActionTag);
	if (!FoundAction || !*FoundAction)
	{
		return false;
	}

	USOO_PlayerActionBase* Action = FoundAction->Get();
	if (IsBlocked(Action))
	{
		return false;
	}

	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	const bool bActivated = Action->TryActivate(OwnerPawn);
	if (bActivated)
	{
		ActiveActionTags.AddTag(ActionTag);
	}

	return bActivated;
}

void USOO_ActionComponent::CancelAction(FGameplayTag ActionTag)
{
	TObjectPtr<USOO_PlayerActionBase>* FoundAction = ActionMap.Find(ActionTag);
	if (!FoundAction || !*FoundAction)
	{
		return;
	}

	USOO_PlayerActionBase* Action = FoundAction->Get();
	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	Action->Cancel(OwnerPawn);

	ActiveActionTags.RemoveTag(ActionTag);
}

bool USOO_ActionComponent::IsActionActive(FGameplayTag ActionTag) const
{
	const TObjectPtr<USOO_PlayerActionBase>* FoundAction = ActionMap.Find(ActionTag);
	return FoundAction && *FoundAction && (*FoundAction)->IsActive();
}

bool USOO_ActionComponent::IsBlocked(const USOO_PlayerActionBase* Action) const
{
	if (!Action)
	{
		return true;
	}

	return ActiveActionTags.HasAny(Action->BlockedWhileActiveTags);
}
