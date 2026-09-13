// SOO_ActionComponent.h
// Phase 3: GAS의 AbilitySystemComponent를 대체하는 경량 컴포넌트.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "SOO_ActionComponent.generated.h"

class USOO_PlayerActionBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class USOO_ActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USOO_ActionComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	TArray<TSubclassOf<USOO_PlayerActionBase>> GrantedActionClasses;

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool TryActivateAction(FGameplayTag ActionTag);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void CancelAction(FGameplayTag ActionTag);

	UFUNCTION(BlueprintPure, Category = "Action")
	bool IsActionActive(FGameplayTag ActionTag) const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<USOO_PlayerActionBase>> ActionMap;

	FGameplayTagContainer ActiveActionTags;

	bool IsBlocked(const USOO_PlayerActionBase* Action) const;
};
