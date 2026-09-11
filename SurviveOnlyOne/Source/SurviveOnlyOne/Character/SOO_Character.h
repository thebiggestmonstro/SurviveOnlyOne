// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SOO_Character.generated.h"

UCLASS()
class SURVIVEONLYONE_API ASOO_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ASOO_Character();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
