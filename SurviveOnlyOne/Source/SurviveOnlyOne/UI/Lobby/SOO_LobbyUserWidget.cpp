// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/SOO_LobbyUserWidget.h"
#include "Player/SOO_PlayerState.h"

#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void USOO_LobbyUserWidget::SetInfo(ASOO_PlayerState* inPlayerState)
{
	LobbyPlayerState = inPlayerState;

	RefreshUI();
}

void USOO_LobbyUserWidget::RefreshUI()
{
	if (LobbyPlayerState == nullptr)
	{
		return;
	}

	// Cache Local variables
	bool IsLocalPlayer = false;
	bool IsPlayerReady = LobbyPlayerState->bIsReady;
	bool IsServer = UKismetSystemLibrary::IsServer(this);

	if (APlayerController* PlayerController = LobbyPlayerState->GetPlayerController())
	{
		IsLocalPlayer = PlayerController->IsLocalController();
	}

	// Hide all Widgets
	Txt_Ready->SetVisibility(ESlateVisibility::Hidden);
	Txt_PlayerName->SetVisibility(ESlateVisibility::Hidden);
	Editable_PlayerName->SetVisibility(ESlateVisibility::Hidden);
	Btn_Ready->SetVisibility(ESlateVisibility::Hidden);
	Btn_KickPlayer->SetVisibility(ESlateVisibility::Hidden);

	// Show Widgets
	if (IsPlayerReady)
	{
		Txt_Ready->SetVisibility(ESlateVisibility::Visible);
	}

	if (IsLocalPlayer && !IsPlayerReady)
	{
		Btn_Ready->SetVisibility(ESlateVisibility::Visible);
	}

	if (IsServer && !IsLocalPlayer)
	{
		Btn_KickPlayer->SetVisibility(ESlateVisibility::Visible);
	}

	Editable_PlayerName->SetText(FText::FromString(LobbyPlayerState->NickName));
	Editable_PlayerName->SetVisibility(ESlateVisibility::Visible);

	if (IsPlayerReady)
	{
		Editable_PlayerName->SetIsReadOnly(true);
	}
	else
	{
		Editable_PlayerName->SetIsReadOnly(!IsLocalPlayer);
	}
}