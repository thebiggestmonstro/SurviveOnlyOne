// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SOO_GameModeBase.generated.h"

class ASOO_DecoyCharacter;

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

private:
	UFUNCTION()
	void SpawnDecoy(int inDeocySpawnCount);

	UPROPERTY()
	int decoySpawnCount = 15;

	UPROPERTY(EditDefaultsOnly, Category = "Decoy")
	TSubclassOf<class ASOO_DecoyCharacter> DecoyCharacterClass;
};
