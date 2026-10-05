// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/SOO_AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/Input/SOO_ActionComponent.h"
#include "Character/SOO_Character.h"

void USOO_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	CachedCharacter = Cast<ACharacter>(TryGetPawnOwner());

	if (CachedCharacter)
	{
		CachedMovementComponent = CachedCharacter->GetCharacterMovement();
	}
}

void USOO_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!CachedCharacter)
	{
		CachedCharacter = Cast<ACharacter>(TryGetPawnOwner());
		if (CachedCharacter)
		{
			CachedMovementComponent = CachedCharacter->GetCharacterMovement();
		}
	}

	if (!CachedCharacter || !CachedMovementComponent)
	{
		return;
	}

	CachedVelocity = CachedMovementComponent->Velocity;
	bCachedIsFalling = CachedMovementComponent->IsFalling();
	bCachedIsCrouching = CachedMovementComponent->IsCrouching();
	bCachedIsDown = Cast<ASOO_Character>(CachedCharacter)->IsCharacterDown();
	CachedActorRotation = CachedCharacter->GetActorRotation();
}

void USOO_AnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	Velocity = CachedVelocity;
	GroundVelocity = FVector(Velocity.X, Velocity.Y, 0.0f);
	Speed = Velocity.Size();
	GroundSpeed = GroundVelocity.Size();
	bIsMoving = GroundSpeed > 3.0f;
	bIsFalling = bCachedIsFalling;
	bIsCrouching = bCachedIsCrouching;
	bIsDown = bCachedIsDown;

	if (bIsMoving)
	{
		const FRotator VelocityRotation = GroundVelocity.Rotation();
		Direction = FMath::FindDeltaAngleDegrees(CachedActorRotation.Yaw, VelocityRotation.Yaw);
	}
	else
	{
		Direction = 0.0f;
	}
}