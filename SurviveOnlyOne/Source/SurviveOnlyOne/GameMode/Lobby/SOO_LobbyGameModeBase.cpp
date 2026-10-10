// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Lobby/SOO_LobbyGameModeBase.h"
#include "Player/SOO_PlayerState.h" 
#include "GameFramework/GameStateBase.h"


ASOO_LobbyGameModeBase::ASOO_LobbyGameModeBase()
{
	bUseSeamlessTravel = true;
}

void ASOO_LobbyGameModeBase::TryStartGame()
{
	if (!CheckAllPlayerReady())
	{
		return;
	}

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this]()
		{
			if (UWorld* World = GetWorld())
			{
				World->ServerTravel(LevelName);
			}
		}, 1.0f, false);
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
