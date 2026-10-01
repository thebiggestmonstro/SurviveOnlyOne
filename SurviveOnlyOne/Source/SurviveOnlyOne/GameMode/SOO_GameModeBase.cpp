// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SOO_GameModeBase.h"
#include "AI/SOO_DecoyCharacter.h" 
#include "GameFramework/PlayerStart.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"

void ASOO_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SpawnDecoy(decoySpawnCount);
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
