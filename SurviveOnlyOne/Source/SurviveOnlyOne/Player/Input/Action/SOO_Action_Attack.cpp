// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Input/Action/SOO_Action_Attack.h"
#include "Player/Input/SOO_ActionComponent.h"
#include "GameFramework/Character.h"

bool USOO_Action_Attack::TryActivate_Implementation(APawn* InstigatorPawn)
{
	bWantsToAttack = true;

	if (bIsActive)
	{
		return true;
	}

	if (!InstigatorPawn || !AttackMontage)
	{
		bWantsToAttack = false;
		return false;
	}

	USOO_ActionComponent* ActionComponent = InstigatorPawn->FindComponentByClass<USOO_ActionComponent>();
	if (!ActionComponent)
	{
		bWantsToAttack = false;
		return false;
	}

	ActionComponent->PlayReplicatedMontage(AttackMontage, AttackPlayRate);
	bIsActive = true;
	return true;
}

void USOO_Action_Attack::Cancel_Implementation(APawn* InstigatorPawn)
{
	bWantsToAttack = false;
}

void USOO_Action_Attack::HandleActionEvent_Implementation(FName EventName, APawn* InstigatorPawn)
{
	if (EventName == FName("AttackHit"))
	{
		PerformHitTrace(InstigatorPawn);
		return;
	}

	if (EventName == FName("AttackEnd"))
	{
		bIsActive = false;
		USOO_ActionComponent* ActionComponent = InstigatorPawn ? InstigatorPawn->FindComponentByClass<USOO_ActionComponent>() : nullptr;

		if (bWantsToAttack && ActionComponent && AttackMontage)
		{
			ActionComponent->PlayReplicatedMontage(AttackMontage, AttackPlayRate);
			bIsActive = true;
			return;
		}

		if (ActionComponent)
		{
			ActionComponent->CancelAction(ActionTag);
		}
	}
}

void USOO_Action_Attack::PerformHitTrace(APawn* InstigatorPawn)
{
	if (!InstigatorPawn || !InstigatorPawn->HasAuthority())
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("SOO_Action_Attack: AttackHit triggered by %s"), *InstigatorPawn->GetName());
}