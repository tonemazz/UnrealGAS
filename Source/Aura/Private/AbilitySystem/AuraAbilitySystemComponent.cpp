/**
 * @file AuraAbilitySystemComponent.cpp
 * @brief Implementation of the Aura Ability System Component.
 *
 * This file implements functionality for initializing the ability system component,
 * adding character abilities, and handling gameplay effect application callbacks.
 */

// Copyright Tone 2025

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/Ability/AuraGameplayAbility.h"

/**
 * @brief Initializes the ability system component by binding necessary delegates and retrieving gameplay tags.
 *
 * This method binds the EffectApplied callback to the OnGameplayEffectAppliedDelegateToSelf delegate,
 * ensuring that any gameplay effects applied to this component will trigger the corresponding logic.
 * It also retrieves the global gameplay tags instance, which may be used elsewhere in the component.
 */
void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
    // Bind the EffectApplied method to be called when a gameplay effect is applied to this component.
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
    
    // Retrieve the singleton instance of gameplay tags.
    const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
}

/**
 * @brief Adds startup abilities to the character's ability system.
 *
 * Iterates through the array of ability classes provided in StartupAbilities, creates a gameplay ability
 * specification (FGameplayAbilitySpec) for each, and assigns them to the component. If the ability is an
 * instance of UAuraGameplayAbility, its startup input tag is added to the spec's dynamic source tags.
 * Finally, the ability is given and immediately activated once.
 *
 * @param StartupAbilities An array of gameplay ability classes to be added to the character.
 */
void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
    for (TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
    {
        // Create an ability specification for the given ability class with an initial level of 1.
        FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
        
        // If the ability is of type UAuraGameplayAbility, add its startup input tag to the spec.
        if (const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
        {
            // Append the startup input tag to the dynamic spec source tags.
            AbilitySpec.GetDynamicSpecSourceTags().AddTag(AuraAbility->StartupInputTag);
            
            GiveAbility(AbilitySpec); 
        }
    }
}

void UAuraAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{

}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
    if (!InputTag.IsValid()) return;

    for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
        {
            AbilitySpecInputReleased(AbilitySpec);
        }
    }
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
    if (!InputTag.IsValid()) return;

    for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
        {
            AbilitySpecInputPressed(AbilitySpec);
            if (!AbilitySpec.IsActive())
            {
                TryActivateAbility(AbilitySpec.Handle);
            }
        }
    }
}

/**
 * @brief Callback function triggered when a gameplay effect is applied to this component.
 *
 * This function is called whenever a gameplay effect is applied to the component. It extracts all asset
 * tags from the effect's specification and broadcasts them via the EffectAssetTags delegate, allowing
 * other systems or UI elements to react to the effect.
 *
 * @param AbilitySystemComponent The ability system component that received the effect.
 * @param EffectSpec The specification of the gameplay effect that was applied.
 * @param ActiveEffectHandle The handle to the active instance of the gameplay effect.
 */
void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
    // Container to collect all asset tags associated with the applied gameplay effect.
    FGameplayTagContainer TagContainer;
    
    // Extract all asset tags from the effect specification.
    EffectSpec.GetAllAssetTags(TagContainer);
    
    // Broadcast the collected tags to any subscribed listeners.
    EffectAssetTags.Broadcast(TagContainer);
}
