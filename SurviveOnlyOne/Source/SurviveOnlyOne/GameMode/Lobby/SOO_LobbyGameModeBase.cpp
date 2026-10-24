// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Lobby/SOO_LobbyGameModeBase.h"
#include "Player/SOO_PlayerState.h" 
#include "Game/SOO_GameInstance.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerController.h"
#include "AdvancedSessionsLibrary.h"
#include "UpdateSessionCallbackProxyAdvanced.h"

ASOO_LobbyGameModeBase::ASOO_LobbyGameModeBase()
{
	bUseSeamlessTravel = true;
}

void ASOO_LobbyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetLevel(TEXT("Fountain"));
}

void ASOO_LobbyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ASOO_PlayerState* PS = NewPlayer->GetPlayerState<ASOO_PlayerState>();

	if (PS)
	{
		NickNameIndex++;
		PS->NickName = FString::Printf(TEXT("User%d"), NickNameIndex);
	}
}

void ASOO_LobbyGameModeBase::TryStartGame()
{
	if (!CheckAllPlayerReady())
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		World->ServerTravel(LevelName);
	}
}

bool ASOO_LobbyGameModeBase::CheckAllPlayerReady()
{
	if (!GameState)
	{
		return false;
	}

	for (APlayerState* PS : GameState->PlayerArray)
	{
		ASOO_PlayerState* SOOPS = Cast<ASOO_PlayerState>(PS);
		if (SOOPS && !SOOPS->bIsReady)
		{
			return false;
		}
	}

	return true;
}

void ASOO_LobbyGameModeBase::SaveConfig(const FString& inLevelName, int32 inMaxPlayerCount, int32 inMaxBotCount)
{
	SetLevel(inLevelName);

	const int32 ClampedMaxPlayerCount = FMath::Clamp(inMaxPlayerCount, 3, 10);
	const int32 ClampedMaxBotCount = FMath::Clamp(inMaxBotCount, 10, 30);

	if (USOO_GameInstance* GameInstance = Cast<USOO_GameInstance>(GetGameInstance()))
	{
		GameInstance->MaxPlayerCount = ClampedMaxPlayerCount;
		GameInstance->MaxBotCount = ClampedMaxBotCount;
	}
}

void ASOO_LobbyGameModeBase::SetLevel(const FString& inLevelName)
{
	if (inLevelName.Equals(TEXT("Fountain"), ESearchCase::IgnoreCase))
	{
		LevelName = TEXT("Level_Fountain");
	}
	else
	{
		LevelName = TEXT("Level_WaterWheel");
	}

	int32 NumConnections = 0;
	int32 NumPrivateConnections = 0;
	bool bIsLAN = false;
	bool bIsDedicated = false;
	bool bAllowInvites = false;
	bool bAllowJoinInProgress = false;
	bool bIsAnticheatEnabled = false;
	int32 BuildUniqueID = 0;
	TArray<FSessionPropertyKeyPair> ExtraSettings;
	EBlueprintResultSwitch Result;

	UAdvancedSessionsLibrary::GetSessionSettings(
		this,
		NumConnections,
		NumPrivateConnections,
		bIsLAN,
		bIsDedicated,
		bAllowInvites,
		bAllowJoinInProgress,
		bIsAnticheatEnabled,
		BuildUniqueID,
		ExtraSettings,
		Result
	);

	if (Result != EBlueprintResultSwitch::OnSuccess)
	{
		return;
	}

	TArray<FSessionPropertyKeyPair> NewOrChangedSettings;
	NewOrChangedSettings.Add(UAdvancedSessionsLibrary::MakeLiteralSessionPropertyString(TEXT("MAP_NAME"), inLevelName));

	TArray<FSessionPropertyKeyPair> ModifiedSettingsArray;
	UAdvancedSessionsLibrary::AddOrModifyExtraSettings(ExtraSettings, NewOrChangedSettings, ModifiedSettingsArray);

	UpdateSessionProxy = UUpdateSessionCallbackProxyAdvanced::UpdateSession(
		this,                  // WorldContextObject
		ModifiedSettingsArray, // Extra Settings
		100,                   // Public Connections
		0,                     // Private Connections
		false,                 // Use LAN
		false,                 // Allow Invites
		true,                  // Allow Join in Progress
		true,                  // Refresh Online Data
		false,                 // Is Dedicated Server
		true                   // Should Advertise
	);

	if (UpdateSessionProxy)
	{
		UpdateSessionProxy->Activate();
	}
}
