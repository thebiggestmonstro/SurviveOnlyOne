// SOO_PawnInputComponent.h
// Phase 4: Lyra의 ULyraHeroComponent 역할.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "SOO_PawnInputComponent.generated.h"

class USOO_InputConfig;
class UInputMappingContext;
class UEnhancedInputComponent;
struct FInputActionValue;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class USOO_PawnInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USOO_PawnInputComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<USOO_InputConfig> InputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	void SetupInputBindings(UEnhancedInputComponent* EnhancedInputComponent);

	void AddDefaultMappingContext(class APlayerController* PC) const;

private:
	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);

	void Input_AbilityTriggered(FGameplayTag InputTag);
};
