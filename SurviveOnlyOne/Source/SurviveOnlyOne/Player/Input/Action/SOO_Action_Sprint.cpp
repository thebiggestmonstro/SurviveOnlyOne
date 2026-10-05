// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Input/Action/SOO_Action_Sprint.h"
#include "Player/Input/SOO_ActionComponent.h"
#include "Character/SOO_Character.h" 

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

bool USOO_Action_Sprint::TryActivate_Implementation(APawn* InstigatorPawn)
{
	ASOO_Character* Character = Cast<ASOO_Character>(InstigatorPawn);
	if (!Character)
	{
		return false;
	}

	UCharacterMovementComponent* Movement = Character->GetCharacterMovement();
	USOO_ActionComponent* ActionComponent = InstigatorPawn->FindComponentByClass<USOO_ActionComponent>();
	if (!Movement || !ActionComponent)
	{
		return false;
	}

	OriginalMaxWalkSpeed = Movement->MaxWalkSpeed;

	const float SprintSpeed = Character->GetCurrentSprintSpeed();

	Movement->MaxWalkSpeed = SprintSpeed;
	ActionComponent->RequestSetMaxWalkSpeed(SprintSpeed);

	bIsActive = true;
	return true;
}

void USOO_Action_Sprint::Cancel_Implementation(APawn* InstigatorPawn)
{
	if (ACharacter* Character = Cast<ACharacter>(InstigatorPawn))
	{
		if (UCharacterMovementComponent* Movement = Character->GetCharacterMovement())
		{
			Movement->MaxWalkSpeed = OriginalMaxWalkSpeed;
		}

		if (USOO_ActionComponent* ActionComponent = InstigatorPawn->FindComponentByClass<USOO_ActionComponent>())
		{
			ActionComponent->RequestSetMaxWalkSpeed(OriginalMaxWalkSpeed);
		}
	}

	bIsActive = false;
}