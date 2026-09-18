// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"
#include "SOO_AnimInstance.generated.h"

class ACharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API USOO_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float Speed = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float Direction = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float GroundSpeed = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector GroundVelocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsMoving = false;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsFalling = false;

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;                  
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;       

private:
	UPROPERTY(Transient)
	TObjectPtr<ACharacter> CachedCharacter;

	UPROPERTY(Transient)
	TObjectPtr<UCharacterMovementComponent> CachedMovementComponent;

	FVector CachedVelocity = FVector::ZeroVector;
	FRotator CachedActorRotation = FRotator::ZeroRotator;
	bool bCachedIsFalling = false;

	void UpdateActionStateData();
};
