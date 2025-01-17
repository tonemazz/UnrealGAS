// Copyright Tone 2025

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes") FGameplayAttributeData Health;
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes") FGameplayAttributeData MaxHealth;
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes") FGameplayAttributeData Mana;
	UPROPERTY(BluePrintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes") FGameplayAttributeData MaxMana;

	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& OldMana);
	UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);

};
