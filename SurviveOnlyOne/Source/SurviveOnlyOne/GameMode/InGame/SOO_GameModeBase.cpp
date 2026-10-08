// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/InGame/SOO_GameModeBase.h"
#include "AI/SOO_DecoyCharacter.h" 
#include "Player/SOO_PlayerState.h"
#include "Actor/SOO_TriggerActor.h"
#include "Character/SOO_Character.h"
#include "Character/SOO_PlayerCharacter.h"

#include "GameFramework/PlayerStart.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "EngineUtils.h"

void ASOO_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SpawnDecoy(decoySpawnCount);

	for (TActorIterator<ASOO_TriggerActor> It(GetWorld()); It; ++It)
	{
		++sunPilarCount;
	}
}

void ASOO_GameModeBase::SpawnDecoy(int inDeocySpawnCount)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), PlayerStarts);

	if (PlayerStarts.Num() == 0)
	{
		return;
	}

	const FVector OriginLocation = PlayerStarts[0]->GetActorLocation();

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(World);
	if (!NavSystem)
	{
		return;
	}

	for (int i = 0; i < inDeocySpawnCount; i++)
	{
		FNavLocation RandomNavLocation;
		const bool bFound = NavSystem->GetRandomReachablePointInRadius(OriginLocation, 50000.0f, RandomNavLocation);
		if (!bFound)
		{
			continue;
		}

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		TSubclassOf<ASOO_DecoyCharacter> ClassToSpawn = DecoyCharacterClass;
		if (!ClassToSpawn)
		{
			ClassToSpawn = ASOO_DecoyCharacter::StaticClass();
		}

		World->SpawnActor<ASOO_DecoyCharacter>(
			ClassToSpawn,
			RandomNavLocation.Location,
			FRotator::ZeroRotator,
			SpawnParams
		);
	}
}

void ASOO_GameModeBase::OnCharacterDeath(ASOO_PlayerCharacter* inDamageCauser, ASOO_Character* inTarget)
{
	if (inDamageCauser == nullptr || inTarget == nullptr)
	{
		return;
	}

	// Attacker
	ASOO_PlayerState* PS = inDamageCauser->GetPS();
	PS->killCount++;

	// Victim
	if (ASOO_PlayerCharacter* TargetPlayerCharacter = Cast<ASOO_PlayerCharacter>(inTarget))
	{
		if (ASOO_PlayerState* TargetPS = TargetPlayerCharacter->GetPS())
		{
			if (bIsGameOver)
			{
				return;
			}

			TargetPS->bIsDead = true;

			if (ASOO_PlayerState* Winner = GetWinner())
			{
				bIsGameOver = true;
				UE_LOG(LogTemp, Warning, TEXT("Win by ALL KILL!!!"));
				EndGame();
			}
		}
	}
}

void ASOO_GameModeBase::OnTriggerActor(ASOO_PlayerState* inPlayerState, ASOO_TriggerActor* triggeredActor)
{
	if (inPlayerState == nullptr || triggeredActor == nullptr)
	{
		return;
	}

	if (!inPlayerState->SunPillars.Contains(triggeredActor))
	{
		inPlayerState->SunPillars.Add(triggeredActor);

		if (ASOO_Character* Character = Cast<ASOO_Character>(inPlayerState->GetPawn()))
		{
			const float NewSprintSpeed = FMath::Max(Character->GetCurrentSprintSpeed() - SpeedHandicapPerPillar, MinWalkSpeed);
			Character->ApplySprintSpeedHandicap(NewSprintSpeed);
		}
	}

	if (!bIsGameOver)
	{
		if (ASOO_PlayerState* Winner = GetWinner())
		{
			bIsGameOver = true;
			UE_LOG(LogTemp, Warning, TEXT("Win by Reaching ALL PILLARS!!!"));
			EndGame();
		}
	}
}

int32 ASOO_GameModeBase::GetAliveCount() const
{
	int32 AliveCount = 0;

	AGameStateBase* GS = GetGameState<AGameStateBase>();
	if (!GS)
	{
		return AliveCount;
	}

	for (APlayerState* PS : GS->PlayerArray)
	{
		if (ASOO_PlayerState* SooPlayerState = Cast<ASOO_PlayerState>(PS))
		{
			if (!SooPlayerState->bIsDead)
			{
				++AliveCount;
			}
		}
	}

	return AliveCount;
}

ASOO_PlayerState* ASOO_GameModeBase::GetWinner() const
{
	AGameStateBase* GS = GetGameState<AGameStateBase>();
	if (!GS)
	{
		return nullptr;
	}

	// Only 1 Player has survived
	if (GetAliveCount() == 1) 
	{
		for (APlayerState* PS : GS->PlayerArray)
		{
			if (ASOO_PlayerState* SooPlayerState = Cast<ASOO_PlayerState>(PS))
			{
				if (!SooPlayerState->bIsDead)
				{
					return SooPlayerState;
				}
			}
		}
	}

	// Some Player has rechead all SunPilars
	for (APlayerState* PS : GS->PlayerArray)
	{
		if (ASOO_PlayerState* SooPlayerState = Cast<ASOO_PlayerState>(PS))
		{
			if (!SooPlayerState->bIsDead)
			{
				if (SooPlayerState->SunPillars.Num() == sunPilarCount)
				{
					return SooPlayerState;
				}
			}
		}
	}

	return nullptr;
}

void ASOO_GameModeBase::EndGame()
{
	if (GetTopKillScore() != nullptr)
	{
		ASOO_PlayerState* topKillScorePS = GetTopKillScore();
		int32 topKillScore = topKillScorePS ? topKillScorePS->killCount : 0;

		UE_LOG(LogTemp, Warning, TEXT("Max kill Score is %d !!!"), topKillScore);
	}
}

ASOO_PlayerState* ASOO_GameModeBase::GetTopKillScore() const
{
	AGameStateBase* GS = GetGameState<AGameStateBase>();
	if (!GS)
	{
		return nullptr;
	}

	ASOO_PlayerState* TopKiller = nullptr;
	int32 HighestKillCount = -1;

	for (APlayerState* PS : GS->PlayerArray)
	{
		if (ASOO_PlayerState* SooPlayerState = Cast<ASOO_PlayerState>(PS))
		{
			if (SooPlayerState->killCount > HighestKillCount)
			{
				HighestKillCount = SooPlayerState->killCount;
				TopKiller = SooPlayerState;
			}
		}
	}

	return TopKiller;
}
