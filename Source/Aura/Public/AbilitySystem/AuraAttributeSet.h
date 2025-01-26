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

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	// Primary Attributes
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes") FGameplayAttributeData Strength; // Attribute declaration 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength) // Generating accessors macro
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes") FGameplayAttributeData Intelligence; // Attribute declaration 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence) // Generating accessors macro
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes") FGameplayAttributeData Resilience; // Attribute declaration 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience) // Generating accessors macro
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes") FGameplayAttributeData Vigor; // Attribute declaration 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor) // Generating accessors macro
	
	// Vital Attributes
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes") FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes") FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes") FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes") FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)

	// Attribute Replication Notification Callbacks
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& OldMana);
	UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	UFUNCTION() void OnRep_Strength(const FGameplayAttributeData& OldStrength);
	UFUNCTION() void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);
	UFUNCTION() void OnRep_Vigor(const FGameplayAttributeData& OldVigor);
	UFUNCTION() void OnRep_Resilience(const FGameplayAttributeData& OldResilience);

private:
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& Props);

};

