// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Input/Action/SOO_PlayerActionBase.h"
#include "SOO_Action_Attack.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API USOO_Action_Attack : public USOO_PlayerActionBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackPlayRate = 2.0f;

	virtual bool TryActivate_Implementation(APawn* InstigatorPawn) override;
	virtual void Cancel_Implementation(APawn* InstigatorPawn) override;
	virtual void HandleActionEvent_Implementation(FName EventName, APawn* InstigatorPawn) override;

protected:
	void PerformHitTrace(APawn* InstigatorPawn);
	bool bWantsToAttack = false;
};
