// Fill out your copyright notice in the Description page of Project Settings.


#include "SOO_OnlieSessionsSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"

USOO_OnlieSessionsSubsystem::USOO_OnlieSessionsSubsystem()
{
}

void USOO_OnlieSessionsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem == nullptr)
	{
		return;
	}

	SessionManager = OnlineSubsystem->GetSessionInterface();
	if (SessionManager.IsValid() == false)
	{
		return;
	}

	FString SubsystemName = OnlineSubsystem->GetSubsystemName().ToString();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, SubsystemName);
	}
}

void USOO_OnlieSessionsSubsystem::CreateSession()
{
	FOnlineSessionSettings Settings;
	Settings.NumPublicConnections = 10;
	Settings.bShouldAdvertise = true;
	Settings.bAllowJoinInProgress = true;
	Settings.bIsLANMatch = true;
	Settings.bUsesPresence = true;
	Settings.bAllowJoinViaPresence = true;
	Settings.bUseLobbiesIfAvailable = true;

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	SessionManager->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, Settings);
}