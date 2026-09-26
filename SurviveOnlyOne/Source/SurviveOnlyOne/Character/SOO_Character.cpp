// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SOO_Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/Input/SOO_ActionComponent.h" 

ASOO_Character::ASOO_Character()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->CrouchedHalfHeight = 88.0f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 0.0f;
}

void ASOO_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASOO_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASOO_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ASOO_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	HandleKnockdown(EventInstigator, DamageCauser);

	return ActualDamage;
}

void ASOO_Character::HandleKnockdown(AController* EventInstigator, AActor* DamageCauser)
{
	if (!HasAuthority() || bIsDown)
	{
		return;
	}

	bIsDown = true; 

	OnRep_IsDown();

	UE_LOG(LogTemp, Log, TEXT("SOO_Character: %s is down (instigator: %s)"), *GetName(), EventInstigator ? *EventInstigator->GetName() : TEXT("Unknown"));
}

void ASOO_Character::OnRep_IsDown()
{
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASOO_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASOO_Character, bIsDown);
}