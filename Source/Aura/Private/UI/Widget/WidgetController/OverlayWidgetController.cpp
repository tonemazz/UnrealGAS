// Copyright Tone 2025


#include "UI/Widget/WidgetController/OverlayWidgetController.h"
#include <AbilitySystem/AuraAttributeSet.h>

/// <function summary>
/// Broadcast initial values to widget(s)
/// </function summary>
void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
}

/// <function summary>
/// </function summary>
void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
}

/// <function summary>
/// </function summary>
void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

/// <function summary>
/// </function summary>
void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
}


