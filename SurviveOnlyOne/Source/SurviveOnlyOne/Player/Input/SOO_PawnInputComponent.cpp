// SOO_PawnInputComponent.cpp

#include "SOO_PawnInputComponent.h"
#include "SOO_InputConfig.h"
#include "SOO_ActionComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

USOO_PawnInputComponent::USOO_PawnInputComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USOO_PawnInputComponent::AddDefaultMappingContext(APlayerController* PC) const
{
	if (!PC || !DefaultMappingContext)
	{
		return;
	}

	if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void USOO_PawnInputComponent::SetupInputBindings(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (!EnhancedInputComponent || !InputConfig)
	{
		return;
	}

	for (const FSOO_TaggedInputAction& Entry : InputConfig->NativeInputActions)
	{
		if (!Entry.InputAction)
		{
			continue;
		}

		if (Entry.InputTag.GetTagName() == FName("InputTag.Native.Move"))
		{
			EnhancedInputComponent->BindAction(
				Entry.InputAction, ETriggerEvent::Triggered, this, &USOO_PawnInputComponent::Input_Move
			);
		}
		else if (Entry.InputTag.GetTagName() == FName("InputTag.Native.Look"))
		{
			EnhancedInputComponent->BindAction(
				Entry.InputAction, ETriggerEvent::Triggered, this, &USOO_PawnInputComponent::Input_Look
			);
		}
	}

	for (const FSOO_TaggedInputAction& Entry : InputConfig->AbilityInputActions)
	{
		if (!Entry.InputAction)
		{
			continue;
		}

		EnhancedInputComponent->BindAction(
			Entry.InputAction, ETriggerEvent::Started,
			this, &USOO_PawnInputComponent::Input_AbilityTriggered, Entry.InputTag
		);

		EnhancedInputComponent->BindAction(
			Entry.InputAction, ETriggerEvent::Completed,
			this, &USOO_PawnInputComponent::Input_AbilityReleased, Entry.InputTag);
	}
}

void USOO_PawnInputComponent::Input_Move(const FInputActionValue& Value)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		return;
	}

	const FVector2D MoveInput = Value.Get<FVector2D>();
	const FRotator ControlRotation = OwnerPawn->GetControlRotation();
	const FRotator YawRotation(0.0, ControlRotation.Yaw, 0.0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	OwnerPawn->AddMovementInput(ForwardDirection, MoveInput.Y);
	OwnerPawn->AddMovementInput(RightDirection, MoveInput.X);
}

void USOO_PawnInputComponent::Input_Look(const FInputActionValue& Value)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		return;
	}

	const FVector2D LookInput = Value.Get<FVector2D>();
	OwnerPawn->AddControllerYawInput(LookInput.X);
	OwnerPawn->AddControllerPitchInput(LookInput.Y);
}

void USOO_PawnInputComponent::Input_AbilityTriggered(FGameplayTag InputTag)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		return;
	}

	if (USOO_ActionComponent* ActionComp = OwnerPawn->FindComponentByClass<USOO_ActionComponent>())
	{
		ActionComp->TryActivateAction(InputTag);
	}
}

void USOO_PawnInputComponent::Input_AbilityReleased(FGameplayTag InputTag)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		return;
	}

	if (USOO_ActionComponent* ActionComp = OwnerPawn->FindComponentByClass<USOO_ActionComponent>())
	{
		ActionComp->CancelAction(InputTag);
	}
}