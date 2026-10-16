// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Lobby/SOO_LobbyGameModeBase.h"
#include "Player/SOO_PlayerState.h" 
#include "Game/SOO_GameInstance.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerController.h"

ASOO_LobbyGameModeBase::ASOO_LobbyGameModeBase()
{
	bUseSeamlessTravel = true;
}

void ASOO_LobbyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ASOO_PlayerState* PS = NewPlayer->GetPlayerState<ASOO_PlayerState>();

	if (PS)
	{
		NickNameIndex++;
		PS->NickName = FString::Printf(TEXT("User%d"), NickNameIndex);
	}
}

void ASOO_LobbyGameModeBase::TryStartGame()
{
	if (!CheckAllPlayerReady())
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		World->ServerTravel(LevelName);
	}
}

bool ASOO_LobbyGameModeBase::CheckAllPlayerReady()
{
	if (!GameState)
	{
		return false;
	}

	for (APlayerState* PS : GameState->PlayerArray)
	{
		ASOO_PlayerState* SOOPS = Cast<ASOO_PlayerState>(PS);
		if (SOOPS && !SOOPS->bIsReady)
		{
			return false;
		}
	}

	return true;
}

void ASOO_LobbyGameModeBase::SaveConfig(const FString& inLevelName, int32 inMaxPlayerCount, int32 inMaxBotCount)
{
	if (inLevelName.Equals(TEXT("Fountain"), ESearchCase::IgnoreCase))
	{
		LevelName = TEXT("Level_Fountain");
	}
	else
	{
		LevelName = TEXT("Level_WaterWheel");
	}

	const int32 ClampedMaxPlayerCount = FMath::Clamp(inMaxPlayerCount, 3, 10);
	const int32 ClampedMaxBotCount = FMath::Clamp(inMaxBotCount, 10, 30);

	if (USOO_GameInstance* GameInstance = Cast<USOO_GameInstance>(GetGameInstance()))
	{
		GameInstance->MaxPlayerCount = ClampedMaxPlayerCount;
		GameInstance->MaxBotCount = ClampedMaxBotCount;
	}
}