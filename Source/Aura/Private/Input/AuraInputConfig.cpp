// Copyright Tone 2025


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag InputTag, bool bLogNotFound) const
{
	for (const FAuraInputAction& Element : InputActions)
	{
		if (Element.InputAction && InputTag == Element.InputTag)
		{
			return Element.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Input Action not found"));
	}

	return nullptr;
}
