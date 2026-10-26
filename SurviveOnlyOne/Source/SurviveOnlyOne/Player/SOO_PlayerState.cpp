// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SOO_PlayerState.h"
#include "Player/Lobby/SOO_LobbyPlayerController.h"
#include "UI/Lobby/SOO_LobbyHUD.h"

#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

void ASOO_PlayerState::BeginPlay()
{
	Super::BeginPlay();

	RefreshLobbyUI();
	OnDestroyed.AddDynamic(this, &ASOO_PlayerState::OnPlayerStateDestroyed);
}

void ASOO_PlayerState::CopyProperties(APlayerState* PlayerState)
{
    Super::CopyProperties(PlayerState);

	ASOO_PlayerState* NewPlayerState = Cast<ASOO_PlayerState>(PlayerState);
	if (NewPlayerState)
	{
		NewPlayerState->NickName = NickName;
	}
}

void ASOO_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASOO_PlayerState, bIsReady);
	DOREPLIFETIME(ASOO_PlayerState, NickName);
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

void ASOO_PlayerState::GetKickedByServer_Implementation()
{
	IOnlineSessionPtr Sessions;
	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		Sessions = Subsystem->GetSessionInterface();
	}

	if (Sessions.IsValid())
	{
		Sessions->DestroySession(NAME_GameSession, FOnDestroySessionCompleteDelegate::CreateUObject(this, &ASOO_PlayerState::OnDestroySessionComplete));
	}
	else
	{
		OnDestroySessionComplete(NAME_GameSession, false);
	}
}

void ASOO_PlayerState::OnRep_IsReady()
{
	RefreshLobbyUI();
}

void ASOO_PlayerState::OnRep_NickName()
{
	RefreshLobbyUI();
}

void ASOO_PlayerState::OnDestroySessionComplete(FName inSessionName, bool bWasSuccessful)
{
	UGameplayStatics::OpenLevel(this, FName(TEXT("Title")), true);
}