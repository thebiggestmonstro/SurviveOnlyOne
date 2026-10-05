// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SOO_GameModeBase.generated.h"

class ASOO_DecoyCharacter;
class ASOO_PlayerCharacter;
class ASOO_Character;
class ASOO_PlayerState;
class ASOO_TriggerActor;

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API ASOO_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void BeginPlay() override;

	void OnCharacterDeath(ASOO_PlayerCharacter* inDamageCauser, ASOO_Character* inTarget);

	void OnTriggerActor(ASOO_PlayerState* inPlayerState, ASOO_TriggerActor* triggeredActor);

private:
	UFUNCTION()
	void SpawnDecoy(int inDeocySpawnCount);

	UPROPERTY()
	int decoySpawnCount = 15;

	UPROPERTY(EditDefaultsOnly, Category = "Decoy")
	TSubclassOf<class ASOO_DecoyCharacter> DecoyCharacterClass;

	UFUNCTION(BlueprintCallable, Category = "GameFlow")
	int32 GetAliveCount() const;

	UFUNCTION(BlueprintCallable, Category = "GameFlow")
	ASOO_PlayerState* GetWinner() const;

	void EndGame();

	UFUNCTION(BlueprintCallable, Category = "GameFlow")
	ASOO_PlayerState* GetTopKillScore() const;

	bool bIsGameOver;

	int sunPilarCount;

	UPROPERTY(EditDefaultsOnly, Category = "Handicap")
	float SpeedHandicapPerPillar = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Handicap")
	float MinWalkSpeed = 300.0f;
};
