// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SOO_DecoyCharacter.h"
#include "Player/Input/SOO_ActionComponent.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/SOO_DecoyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ASOO_DecoyCharacter::ASOO_DecoyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AIControllerClass = ASOO_DecoyAIController::StaticClass();

	ActionComponent = CreateDefaultSubobject<USOO_ActionComponent>(TEXT("ActionComponent"));

	GetCharacterMovement()->GetNavMovementProperties()->bUseAccelerationForPaths = true;
	GetCharacterMovement()->GetNavMovementProperties()->bUseFixedBrakingDistanceForPaths = true;
}

void ASOO_DecoyCharacter::OnRep_IsDown()
{
	Super::OnRep_IsDown();

	if (ASOO_DecoyAIController* AIController = Cast<ASOO_DecoyAIController>(GetController()))
	{
		if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
		{
			BlackboardComp->SetValueAsBool(TEXT("IsDown"), true);
		}
	}
}
