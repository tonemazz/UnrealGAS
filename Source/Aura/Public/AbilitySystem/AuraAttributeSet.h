// Copyright Tone 2025

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"


// Attribute Accessor Macro
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY() UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY() AActor* SourceAvatarActor = nullptr;
	UPROPERTY() AController* SourceController = nullptr;
	UPROPERTY() ACharacter* SourceCharacter = nullptr;

	UPROPERTY() UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY() AActor* TargetAvatarActor = nullptr;
	UPROPERTY() AController* TargetController = nullptr;
	UPROPERTY() ACharacter* TargetCharacter = nullptr;
};

// Template alias for a function pointer
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	// Maps an FGameplayTag to an FGameplayAttribute function pointer
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	
	// Primary Attributes
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes") FGameplayAttributeData Strength; // Attribute declaration 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength) // Generating accessors macro
	
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes") FGameplayAttributeData Intelligence; // Attribute declaration 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence) // Generating accessors macro
	
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes") FGameplayAttributeData Resilience; // Attribute declaration 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience) // Generating accessors macro
	
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes") FGameplayAttributeData Vigor; // Attribute declaration 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor) // Generating accessors macro

	// Secondary (Derived) Attributes
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes") FGameplayAttributeData Armor; // Reduces damage taken
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor) // Generating accessors macro
	
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes") FGameplayAttributeData ArmorPenetration; // Ignores percentage of enemy armor + increases CritChance
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration) // Generating accessors macro
	
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes") FGameplayAttributeData BlockChance; // Chance to block, which decreases incoming damage by 50%
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance) // Generating accessors macro
	
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_CritChance, Category = "Secondary Attributes") FGameplayAttributeData CritChance; // Chance to score crit hit, dealing double damage + CritBonusDamage
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CritChance) // Generating accessors macro
	
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_CritBonusDamage, Category = "Secondary Attributes") FGameplayAttributeData CritBonusDamage; // Amount of bonus damage added upon critical hit
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CritBonusDamage) // Generating accessors macro
	
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_CritResistance, Category = "Secondary Attributes") FGameplayAttributeData CritResistance; // Reduces chance for enemy to score a crit hit
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CritResistance) // Generating accessors macro
	
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_HealthRegenPerSecond, Category = "Secondary Attributes") FGameplayAttributeData HealthRegenPerSecond; // Amount of health regenerated every second
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegenPerSecond) // Generating accessors macro
	
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_ManaRegenPerSecond, Category = "Secondary Attributes") FGameplayAttributeData ManaRegenPerSecond; // Amount of mana regenerated every second
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegenPerSecond) // Generating accessors macro
	
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes") FGameplayAttributeData MaxHealth; // Max attainable health
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)
	
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes") FGameplayAttributeData MaxMana; // Max attainable mana
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)
	
	// Vital Attributes
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes") FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes") FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)
	
	// Attribute Replication Notification Callbacks
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& OldMana);
	UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	UFUNCTION() void OnRep_Strength(const FGameplayAttributeData& OldStrength);
	UFUNCTION() void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);
	UFUNCTION() void OnRep_Vigor(const FGameplayAttributeData& OldVigor);
	UFUNCTION() void OnRep_Resilience(const FGameplayAttributeData& OldResilience);
	
	// Attribute Replication Notification Callbacks for Secondary Attributes
	UFUNCTION() void OnRep_Armor(const FGameplayAttributeData& OldArmor);
	UFUNCTION() void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration);
	UFUNCTION() void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance);
	UFUNCTION() void OnRep_CritChance(const FGameplayAttributeData& OldCritChance);
	UFUNCTION() void OnRep_CritBonusDamage(const FGameplayAttributeData& OldCritBonusDamage);
	UFUNCTION() void OnRep_CritResistance(const FGameplayAttributeData& OldCritResistance);
	UFUNCTION() void OnRep_HealthRegenPerSecond(const FGameplayAttributeData& OldHealthRegenPerSecond);
	UFUNCTION() void OnRep_ManaRegenPerSecond(const FGameplayAttributeData& OldManaRegenPerSecond);


private:
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& Props);

};

