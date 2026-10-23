// Fill out your copyright notice in the Description page of Project Settings.


#include "SOO_OnlieSessionsSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"
#include "Kismet/GameplayStatics.h"

USOO_OnlieSessionsSubsystem::USOO_OnlieSessionsSubsystem()
	: CreateCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &USOO_OnlieSessionsSubsystem::OnCreate))
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
}

void USOO_OnlieSessionsSubsystem::CreateSession()
{
	FNamedOnlineSession* ExistingSession = SessionManager->GetNamedSession(NAME_GameSession);
	if (ExistingSession)
	{
		SessionManager->DestroySession(NAME_GameSession);
		return;
	}

	CreateCompleteDelegateHandle = SessionManager->AddOnCreateSessionCompleteDelegate_Handle(CreateCompleteDelegate);

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

void USOO_OnlieSessionsSubsystem::OnCreate(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UGameplayStatics::OpenLevel(this, "Lobby", true, FString("listen"));
	}

	SessionManager->ClearOnCreateSessionCompleteDelegate_Handle(CreateCompleteDelegateHandle);
}
