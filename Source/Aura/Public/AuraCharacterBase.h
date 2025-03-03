// Tone

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"



class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	// Combat Interface
	// End Combat Interface

protected:
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<class USkeletalMeshComponent> Weapon;

	// This property MUST be set in the blueprint or we will possibly crash
	// The socket name should be the same as the socket name in the weapon mesh, and the socket should exist.
	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;

	virtual FVector GetCombatSocketLocation() override;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	virtual void SetupAbilityActorInfo();


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes") TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes") TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes") TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void InitializePrimaryAttributes();
	void InitializeSecondaryAttributes();
	void InitializeVitalAttributes();

	void AddCharacterAbilities();

private:

	UPROPERTY(EditAnywhere, Category="Abilities") TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	void ApplyEffectToTarget(UAbilitySystemComponent* ASC, const TSubclassOf<UGameplayEffect>& EffectClass) const;
};
