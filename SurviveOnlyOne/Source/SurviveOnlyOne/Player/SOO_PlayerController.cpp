// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SOO_PlayerController.h"
#include "EnhancedInputSubsystems.h"

void ASOO_PlayerController::BeginPlay()
{
	if (!DefaultMappingContext)
	{
		return;
	}

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}
