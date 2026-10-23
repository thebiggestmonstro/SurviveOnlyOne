// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Room/SOO_RoomListWidget.h"
#include "SOO_RoomItemWidget.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"

bool USOO_RoomListWidget::Initialize()
{
    if (Super::Initialize() == false)
    {
        return false;
    }

    SetInfo();

    return true;
}

void USOO_RoomListWidget::SetInfo()
{
    Rooms.Empty();

    for (int32 i = 0; i < 10; i++)
    {
        if (RoomItemWidgetClass == nullptr)
        {
            continue;
        }

        USOO_RoomItemWidget* ChildWidget = CreateWidget<USOO_RoomItemWidget>(GetWorld(), RoomItemWidgetClass);
        if (ChildWidget == nullptr)
        {
            continue;
        }

        RoomList->AddChildToWrapBox(ChildWidget);
        Rooms.Add(ChildWidget);
    }

    RefreshUI();
}

void USOO_RoomListWidget::RefreshUI()
{
    const int32 SessionLength = SessionInfos.Num();

    for (int32 i = 0; i < Rooms.Num(); i++)
    {
        const int32 Index = i;

        if (Index < SessionLength)
        {
            Rooms[Index]->SetVisibility(ESlateVisibility::Visible);
            FBlueprintSessionResult Result = SessionInfos[Index];
            Rooms[Index]->SetInfo(Result);
        }
        else
        {
            Rooms[Index]->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}