// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SOO_LobbyHUD.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API ASOO_LobbyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Lobby")
	void RefreshUI();
};
