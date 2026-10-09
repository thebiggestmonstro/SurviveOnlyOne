// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SOO_PlayerState.h"
#include "Player/Lobby/SOO_LobbyPlayerController.h"
#include "UI/Lobby/SOO_LobbyHUD.h"

void ASOO_PlayerState::BeginPlay()
{
	Super::BeginPlay();

	RefreshLobbyUI();
	OnDestroyed.AddDynamic(this, &ASOO_PlayerState::OnPlayerStateDestroyed);
}

void ASOO_PlayerState::CopyProperties(APlayerState* PlayerState)
{
    Super::CopyProperties(PlayerState);

}

void ASOO_PlayerState::RefreshLobbyUI()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	if (ASOO_LobbyPlayerController* LobbyPC = Cast<ASOO_LobbyPlayerController>(World->GetFirstPlayerController()))
	{
		if (ASOO_LobbyHUD* HUD = LobbyPC->GetHUD<ASOO_LobbyHUD>())
		{
			HUD->RefreshUI();
		}
	}
}

void ASOO_PlayerState::OnPlayerStateDestroyed(AActor* DestroyedActor)
{
	RefreshLobbyUI();
}