// Tone

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"



class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere, Category = "Combat") TObjectPtr<class USkeletalMeshComponent> Weapon;
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	TObjectPtr<UAttributeSet> AttributeSet;
	virtual void SetupAbilityActorInfo();


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes") TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes") TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	void InitializePrimaryAttributes();
	void InitializeSecondaryAttributes();

private:

	void ApplyEffectToTarget(UAbilitySystemComponent* ASC, const TSubclassOf<UGameplayEffect>& EffectClass) const;
};
