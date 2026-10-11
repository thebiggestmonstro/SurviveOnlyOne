// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SOO_LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API ASOO_LobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void HandleReadyButton();

	UFUNCTION(Server, Reliable)
	void ServerHandleReadyButton();

	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void HandleChangeNickname(const FString& InNickName);

	UFUNCTION(Server, Reliable)
	void ServerHandleChangeNickname(const FString& InNickName);
};
