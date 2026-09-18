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

	UFUNCTION(BlueprintPure, Category = "Action")
	bool HasActiveTag(FGameplayTag Tag) const { return ActiveActionTags.HasTag(Tag); }

	const FGameplayTagContainer& GetActiveTags() const { return ActiveActionTags; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<USOO_PlayerActionBase>> ActionMap;

	FGameplayTagContainer ActiveActionTags;

	bool IsBlocked(const USOO_PlayerActionBase* Action) const;
};
