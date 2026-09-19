// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Input/Action/SOO_PlayerActionBase.h"
#include "SOO_Action_Crouch.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API USOO_Action_Crouch : public USOO_PlayerActionBase
{
	GENERATED_BODY()
	
public:
	virtual bool TryActivate_Implementation(APawn* InstigatorPawn) override;
	virtual void Cancel_Implementation(APawn* InstigatorPawn) override;
};
