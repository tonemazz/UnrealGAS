// Copyright Tone 2025


#include "UI/Widget/WidgetController/OverlayWidgetController.h"
#include <AbilitySystem/AuraAttributeSet.h>

#include "AbilitySystem/AuraAbilitySystemComponent.h"

/// <function summary>
/// Broadcast initial values to widget(s)
/// </function summary>
void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

/// <function summary>
/// </function summary>
void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	// Bind Lambdas to delegates
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate( AuraAttributeSet->GetHealthAttribute()).AddLambda( [this] (const FOnAttributeChangeData& Data){ OnHealthChanged.Broadcast(Data.NewValue); } );
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate( AuraAttributeSet->GetMaxHealthAttribute()).AddLambda( [this] (const FOnAttributeChangeData& Data){ OnMaxHealthChanged.Broadcast(Data.NewValue); } );
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate( AuraAttributeSet->GetManaAttribute()).AddLambda( [this] (const FOnAttributeChangeData& Data){ OnManaChanged.Broadcast(Data.NewValue); } );
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate( AuraAttributeSet->GetMaxManaAttribute()).AddLambda( [this] (const FOnAttributeChangeData& Data){ OnMaxManaChanged.Broadcast(Data.NewValue); } );

	// Handles the asset tags associated with a gameplay effect for use by the widget controller
	// Broadcast by FEffectAssetTags in AuraAbilitySystemComponent
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				// Only message-type tags should be looked up here
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
				
			}
		});

	
}



void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
