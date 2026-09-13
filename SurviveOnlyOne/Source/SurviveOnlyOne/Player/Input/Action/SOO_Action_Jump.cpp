// SOO_Action_Jump.cpp

#include "SOO_Action_Jump.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

bool USOO_Action_Jump::TryActivate_Implementation(APawn* InstigatorPawn)
{
	ACharacter* Character = Cast<ACharacter>(InstigatorPawn);
	if (!Character || Character->GetCharacterMovement()->IsFalling())
	{
		return false;
	}

	Character->Jump();
	bIsActive = true;
	return true;
}

void USOO_Action_Jump::Cancel_Implementation(APawn* InstigatorPawn)
{
	if (ACharacter* Character = Cast<ACharacter>(InstigatorPawn))
	{
		Character->StopJumping();
	}

	bIsActive = false;
}
