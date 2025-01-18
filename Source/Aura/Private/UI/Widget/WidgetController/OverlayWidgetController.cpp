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


