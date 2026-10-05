#include "SOO_ActionComponent.h"
#include "Action/SOO_PlayerActionBase.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"

USOO_ActionComponent::USOO_ActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
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

void USOO_ActionComponent::NotifyActionEvent(FGameplayTag ActionTag, FName EventName)
{
	TObjectPtr<USOO_PlayerActionBase>* FoundAction = ActionMap.Find(ActionTag);
	if (!FoundAction || !*FoundAction)
	{
		return;
	}

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	(*FoundAction)->HandleActionEvent(EventName, OwnerPawn);
}

void USOO_ActionComponent::PlayReplicatedMontage(UAnimMontage* Montage, float PlayRate)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter || !Montage)
	{
		return;
	}

	OwnerCharacter->PlayAnimMontage(Montage, PlayRate);

	if (OwnerCharacter->HasAuthority())
	{
		MulticastPlayMontage(Montage, PlayRate);
	}
	else
	{
		ServerPlayMontage(Montage, PlayRate);
	}
}

void USOO_ActionComponent::ServerPlayMontage_Implementation(UAnimMontage* Montage, float PlayRate)
{
	MulticastPlayMontage(Montage, PlayRate);
}

void USOO_ActionComponent::MulticastPlayMontage_Implementation(UAnimMontage* Montage, float PlayRate)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter || !Montage)
	{
		return;
	}

	if (!OwnerCharacter->IsLocallyControlled())
	{
		OwnerCharacter->PlayAnimMontage(Montage, PlayRate);
	}
}

void USOO_ActionComponent::RequestSetMaxWalkSpeed(float NewMaxWalkSpeed)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		return;
	}

	if (OwnerCharacter->HasAuthority())
	{
		if (UCharacterMovementComponent* Movement = OwnerCharacter->GetCharacterMovement())
		{
			Movement->MaxWalkSpeed = NewMaxWalkSpeed;
		}
	}
	else
	{
		ServerSetMaxWalkSpeed(NewMaxWalkSpeed);
	}
}

void USOO_ActionComponent::ServerSetMaxWalkSpeed_Implementation(float NewMaxWalkSpeed)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		return;
	}

	if (UCharacterMovementComponent* Movement = OwnerCharacter->GetCharacterMovement())
	{
		Movement->MaxWalkSpeed = NewMaxWalkSpeed;
	}
}