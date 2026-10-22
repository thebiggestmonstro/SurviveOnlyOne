// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Room/SOO_RoomItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void USOO_RoomItemWidget::SetInfo(FBlueprintSessionResult InSessionResult)
{
    Result = InSessionResult;
    RefreshUI();
}

void USOO_RoomItemWidget::RefreshUI()
{
    Txt_RoomName->SetText(FText());
    Txt_PlayerCount->SetText(FText());
    Txt_MapName->SetText(FText());
}