// SOO_PlayerActionBase.h
// Phase 3: GAS의 GameplayAbility를 대체하는 최소 인터페이스.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "SOO_PlayerActionBase.generated.h"

class APawn;

UCLASS(Abstract, BlueprintType, Blueprintable)
class USOO_PlayerActionBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	FGameplayTag ActionTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	FGameplayTagContainer BlockedWhileActiveTags;

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool TryActivate(APawn* InstigatorPawn);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void Cancel(APawn* InstigatorPawn);

	UFUNCTION(BlueprintPure, Category = "Action")
	bool IsActive() const { return bIsActive; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Action")
	bool bIsActive = false;
};
