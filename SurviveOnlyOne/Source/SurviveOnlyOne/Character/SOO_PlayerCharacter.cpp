// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SOO_PlayerCharacter.h"
#include "Player/Input/SOO_ActionComponent.h"
#include "Player/Input/SOO_PawnInputComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

ASOO_PlayerCharacter::ASOO_PlayerCharacter()
{
    if (UCharacterMovementComponent* MovementComp = GetCharacterMovement())
    {
        MovementComp->bOrientRotationToMovement = true;
    }

    bUseControllerRotationYaw = false;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 500.0f; 
    CameraBoom->bUsePawnControlRotation = true; 

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
    FollowCamera->bUsePawnControlRotation = false; 

    ActionComponent = CreateDefaultSubobject<USOO_ActionComponent>(TEXT("ActionComponent"));
    PawnInputComponent = CreateDefaultSubobject<USOO_PawnInputComponent>(TEXT("PawnInputComponent"));
}

void ASOO_PlayerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController); 
}

void ASOO_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent); 

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        PawnInputComponent->SetupInputBindings(EIC);
    }
}