// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Lobby/SOO_LobbyPlayerController.h"
#include "Player/SOO_PlayerState.h"
#include "GameMode/Lobby/SOO_LobbyGameModeBase.h"

void ASOO_LobbyPlayerController::HandleReadyButton()
{
	ASOO_PlayerState* PS = GetPlayerState<ASOO_PlayerState>();
	if (!PS || PS->bIsReady)
	{
		return;
	}

	PS->bIsReady = true;
	PS->RefreshLobbyUI();

	ServerHandleReadyButton();
}

void ASOO_LobbyPlayerController::ServerHandleReadyButton_Implementation()
{
	if (ASOO_PlayerState* PS = GetPlayerState<ASOO_PlayerState>())
	{
		PS->bIsReady = true;
		PS->RefreshLobbyUI();
	}

	if (ASOO_LobbyGameModeBase* GM = GetWorld()->GetAuthGameMode<ASOO_LobbyGameModeBase>())
	{
		GM->TryStartGame();
	}
}
