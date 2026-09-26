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

	UFUNCTION(BlueprintPure, Category = "Knockdown")
	bool IsCharacterDown() const { return bIsDown; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_IsDown, BlueprintReadOnly, Category = "Knockdown")
	bool bIsDown = false;

	UFUNCTION()
	void OnRep_IsDown();

	void HandleKnockdown(AController* EventInstigator, AActor* DamageCauser);
};
