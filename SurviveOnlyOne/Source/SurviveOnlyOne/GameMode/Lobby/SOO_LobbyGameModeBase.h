// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SOO_LobbyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API ASOO_LobbyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASOO_LobbyGameModeBase();

	void TryStartGame();

	bool CheckAllPlayerReady();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lobby")
	FString LevelName;
};
