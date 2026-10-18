// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/SOO_LobbyWidget.h"
#include "Player/SOO_PlayerState.h"
#include "UI/Lobby/SOO_LobbyUserWidget.h"

#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

bool USOO_LobbyWidget::Initialize()
{
    if (Super::Initialize() == false)
    {
        return false;
    }

    SetInfo();

    return true;
}

void USOO_LobbyWidget::SetInfo()
{
    LobbyUsers.Empty();

    for (int32 i = 0; i < 10; i++)
    {
        if (LobbyUserWidgetClass == nullptr)
        {
            continue;
        }

        USOO_LobbyUserWidget* ChildWidget = CreateWidget<USOO_LobbyUserWidget>(GetWorld(), LobbyUserWidgetClass);
        if (ChildWidget == nullptr)
        {
            continue;
        }

        UserList->AddChildToVerticalBox(ChildWidget);
        LobbyUsers.Add(ChildWidget);
    }

    RefreshUI();
}

ASOO_PlayerState* USOO_LobbyWidget::GetPlayerStateFromIndex(int32 Index)
{
    AGameStateBase* GS = GetWorld() ? GetWorld()->GetGameState() : nullptr;
    if (!IsValid(GS) || !GS->PlayerArray.IsValidIndex(Index))
    {
        return nullptr;
    }

    return Cast<ASOO_PlayerState>(GS->PlayerArray[Index]);
}

void USOO_LobbyWidget::RefreshUI()
{
    // Cache Player Length(Count)
    int32 LocalPlayerLength = 0;
    AGameStateBase* GS = GetWorld() ? GetWorld()->GetGameState() : nullptr;
    if (IsValid(GS))
    {
        LocalPlayerLength = GS->PlayerArray.Num();
    }

    // Show or Hide Lobby User Widget
    for (int32 LocalIndex = 0; LocalIndex < LobbyUsers.Num(); ++LocalIndex)
    {
        USOO_LobbyUserWidget* UserWidget = LobbyUsers[LocalIndex];
        if (!UserWidget)
        {
            continue;
        }

        if (LocalIndex < LocalPlayerLength)
        {
            UserWidget->SetVisibility(ESlateVisibility::Visible);
            UserWidget->SetInfo(GetPlayerStateFromIndex(LocalIndex));
        }
        else
        {
            UserWidget->SetVisibility(ESlateVisibility::Collapsed);
        }
    }

    // Show Game Config Button
    if (Btn_GameConfig)
    {
        const bool bIsServer = GetWorld() && GetWorld()->GetNetMode() != NM_Client;
        Btn_GameConfig->SetVisibility(bIsServer ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }
}