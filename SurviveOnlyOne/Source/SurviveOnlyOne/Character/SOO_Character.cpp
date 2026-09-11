// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SOO_Character.h"

ASOO_Character::ASOO_Character()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASOO_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASOO_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASOO_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

