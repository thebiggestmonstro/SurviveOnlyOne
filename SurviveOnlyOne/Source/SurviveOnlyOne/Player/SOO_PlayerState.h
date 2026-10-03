// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SOO_PlayerState.generated.h"

class ASOO_TriggerActor;

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API ASOO_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	bool bIsDead;

	UPROPERTY()
	TSet<TObjectPtr<ASOO_TriggerActor>> SunPillars;

	UPROPERTY()
	int killCount;
};
