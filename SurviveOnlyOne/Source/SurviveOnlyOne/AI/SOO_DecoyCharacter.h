// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SOO_Character.h"
#include "SOO_DecoyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API ASOO_DecoyCharacter : public ASOO_Character
{
	GENERATED_BODY()
	
public:
	ASOO_DecoyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Action")
	class USOO_ActionComponent* ActionComponent;

protected:
	virtual void OnRep_IsDown() override;
};
