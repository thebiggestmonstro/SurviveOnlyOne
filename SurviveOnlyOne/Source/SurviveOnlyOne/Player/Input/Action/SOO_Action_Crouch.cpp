// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Input/Action/SOO_Action_Crouch.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

bool USOO_Action_Crouch::TryActivate_Implementation(APawn* InstigatorPawn)
{
	ACharacter* Character = Cast<ACharacter>(InstigatorPawn);
	if (!Character || !Character->CanCrouch())
	{
		return false;
	}

	if (Character->GetCharacterMovement()->IsFalling())
	{
		return false;
	}

	Character->Crouch();
	bIsActive = true;
	return true;
}

void USOO_Action_Crouch::Cancel_Implementation(APawn* InstigatorPawn)
{
	if (ACharacter* Character = Cast<ACharacter>(InstigatorPawn))
	{
		Character->UnCrouch();
	}

	bIsActive = false;
}
