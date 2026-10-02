// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SOO_TriggerActor.h"
#include "Player/SOO_PlayerState.h"
#include "Character/SOO_PlayerCharacter.h"
#include "GameMode/SOO_GameModeBase.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

ASOO_TriggerActor::ASOO_TriggerActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(SceneRoot);
	Capsule->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneRoot);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);	

	Capsule->OnComponentBeginOverlap.AddDynamic(this,&ASOO_TriggerActor::OnCapsuleBeginOverlap);
}

void ASOO_TriggerActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (!HasAuthority())
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ASOO_TriggerActor::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}

	ASOO_PlayerCharacter* PlayerCharacter = Cast<ASOO_PlayerCharacter>(OtherActor);
	if (!PlayerCharacter)
	{
		return;
	}

	ASOO_PlayerState* PlayerState = PlayerCharacter->GetPS();
	if (!PlayerState)
	{
		return;
	}

	ASOO_GameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASOO_GameModeBase>();
	if (!GameMode)
	{
		return;
	}

	GameMode->OnTriggerActor(PlayerState, this);
}