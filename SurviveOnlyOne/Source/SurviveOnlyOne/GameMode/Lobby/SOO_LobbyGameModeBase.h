// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SOO_LobbyGameModeBase.generated.h"

class APlayerController;
class UUpdateSessionCallbackProxyAdvanced;

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API ASOO_LobbyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASOO_LobbyGameModeBase();

	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	void TryStartGame();

	bool CheckAllPlayerReady();

	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void SaveConfig(const FString& inLevelName, int32 inMaxPlayerCount, int32 inMaxBotCount);

	void SetLevel(const FString& inLevelName);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lobby")
	FString LevelName;

	UPROPERTY()
	int32 NickNameIndex;

private:
	UPROPERTY()
	TObjectPtr<UUpdateSessionCallbackProxyAdvanced> UpdateSessionProxy;
};
