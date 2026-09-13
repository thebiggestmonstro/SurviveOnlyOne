// SOO_InputConfig.cpp

#include "SOO_InputConfig.h"

const UInputAction* USOO_InputConfig::FindNativeActionForTag(const FGameplayTag& InputTag) const
{
	return FindActionForTagInternal(NativeInputActions, InputTag);
}

const UInputAction* USOO_InputConfig::FindAbilityActionForTag(const FGameplayTag& InputTag) const
{
	return FindActionForTagInternal(AbilityInputActions, InputTag);
}

const UInputAction* USOO_InputConfig::FindActionForTagInternal(const TArray<FSOO_TaggedInputAction>& Actions, const FGameplayTag& InputTag)
{
	for (const FSOO_TaggedInputAction& Entry : Actions)
	{
		if (Entry.InputTag == InputTag && Entry.InputAction)
		{
			return Entry.InputAction;
		}
	}

	return nullptr;
}
