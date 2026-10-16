// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/InGame/SOO_GameStateBase.h"

void ASOO_GameStateBase::Multicast_GameResult_Implementation(const FString& WinnerName, const FString& MaxKillerName, int32 MaxKillCount)
{
	OnGameResult(WinnerName, MaxKillerName, MaxKillCount);
}
