// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SOO_PlayerState.generated.h"

class ASOO_TriggerActor;

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API ASOO_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void BeginPlay() override;

	virtual void CopyProperties(APlayerState* PlayerState) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void RefreshLobbyUI();

	UFUNCTION()
	void OnPlayerStateDestroyed(AActor* DestroyedActor);

public:
	UPROPERTY()
	bool bIsDead;

	UPROPERTY()
	TSet<TObjectPtr<ASOO_TriggerActor>> SunPillars;

	UPROPERTY()
	int killCount;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_IsReady, Category = "Lobby")
	bool bIsReady;

private:
	UFUNCTION()
	void OnRep_IsReady();
};
