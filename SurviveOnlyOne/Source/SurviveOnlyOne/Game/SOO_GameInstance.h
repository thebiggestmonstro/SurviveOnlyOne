// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SOO_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API USOO_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	int32 MaxPlayerCount = 3;

	UPROPERTY()
	int32 MaxBotCount = 10;
};
