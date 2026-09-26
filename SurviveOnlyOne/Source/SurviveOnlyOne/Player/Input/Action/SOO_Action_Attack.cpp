// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Input/Action/SOO_Action_Attack.h"
#include "Player/Input/SOO_ActionComponent.h"
#include "Character/SOO_Character.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

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

	if (Cast<ASOO_Character>(InstigatorPawn)->IsCharacterDown())
	{
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
	if (EventName == FName("AttackWindow_Begin"))
	{
		BeginSweepWindow(InstigatorPawn);
		return;
	}

	if (EventName == FName("AttackWindow_Tick"))
	{
		TickSweepWindow(InstigatorPawn);
		return;
	}

	if (EventName == FName("AttackWindow_End"))
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

FVector USOO_Action_Attack::GetCurrentFistLocation(APawn* InstigatorPawn) const
{
	return InstigatorPawn->GetActorLocation() + InstigatorPawn->GetActorForwardVector() * AttackRange;
}

void USOO_Action_Attack::BeginSweepWindow(APawn* InstigatorPawn)
{
	if (!InstigatorPawn || !InstigatorPawn->HasAuthority())
	{
		return;
	}

	AlreadyHitActorsThisSwing.Empty();

	PrevFistLocation = GetCurrentFistLocation(InstigatorPawn);
	bHasPrevFistLocation = true;
}

void USOO_Action_Attack::TickSweepWindow(APawn* InstigatorPawn)
{
	if (!InstigatorPawn || !InstigatorPawn->HasAuthority())
	{
		return;
	}

	if (!bHasPrevFistLocation)
	{
		BeginSweepWindow(InstigatorPawn);
		return;
	}

	const FVector CurrentFistLocation = GetCurrentFistLocation(InstigatorPawn);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(InstigatorPawn);

	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::SphereTraceMulti(
		InstigatorPawn,
		PrevFistLocation,
		CurrentFistLocation,
		AttackRadius,
		UEngineTypes::ConvertToTraceType(ECC_Pawn),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		HitResults,
		true
	);

	for (const FHitResult& Hit : HitResults)
	{
		AActor* HitActor = Hit.GetActor();
		if (!HitActor || AlreadyHitActorsThisSwing.Contains(HitActor))
		{
			continue;
		}
		
		ASOO_Character* HitCharacter = Cast<ASOO_Character>(HitActor);
		if (!HitCharacter)
		{
			continue;
		}

		AlreadyHitActorsThisSwing.Add(HitActor);

		UGameplayStatics::ApplyDamage(
			HitCharacter,
			1.0f,
			InstigatorPawn->GetController(),
			InstigatorPawn,
			UDamageType::StaticClass()
		);

		UE_LOG(LogTemp, Log, TEXT("SOO_Action_Attack: %s hit %s"), *InstigatorPawn->GetName(), *HitActor->GetName());
	}

	PrevFistLocation = CurrentFistLocation;
}