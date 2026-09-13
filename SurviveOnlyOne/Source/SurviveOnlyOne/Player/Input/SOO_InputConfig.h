// SOO_InputConfig.h
// Phase 2: 태그(GameplayTag) 기준으로 InputAction을 매핑하는 데이터 애셋.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "SOO_InputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FSOO_TaggedInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputAction = nullptr;
};

UCLASS(BlueprintType, Const)
class USOO_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<FSOO_TaggedInputAction> NativeInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<FSOO_TaggedInputAction> AbilityInputActions;

	const UInputAction* FindNativeActionForTag(const FGameplayTag& InputTag) const;
	const UInputAction* FindAbilityActionForTag(const FGameplayTag& InputTag) const;

private:
	static const UInputAction* FindActionForTagInternal(
		const TArray<FSOO_TaggedInputAction>& Actions,
		const FGameplayTag& InputTag
	);
};
