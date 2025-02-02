// Tone


#include "AuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	

}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraCharacterBase::SetupAbilityActorInfo() // virtual function
{
}



void AAuraCharacterBase::InitializePrimaryAttributes()
{
	ApplyEffectToTarget(AbilitySystemComponent, DefaultPrimaryAttributes);
}

void AAuraCharacterBase::InitializeSecondaryAttributes()
{
	ApplyEffectToTarget(AbilitySystemComponent, DefaultSecondaryAttributes);
}

void AAuraCharacterBase::InitializeVitalAttributes()
{
	ApplyEffectToTarget(AbilitySystemComponent, DefaultVitalAttributes);
}

void AAuraCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority()) return;

	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->AddCharacterAbilities(StartupAbilities);
}

void AAuraCharacterBase::ApplyEffectToTarget(UAbilitySystemComponent* ASC, const TSubclassOf<UGameplayEffect>& EffectClass) const
{
	if (EffectClass != nullptr && ASC)
	{
		FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1, EffectContextHandle);
		FActiveGameplayEffectHandle ActiveEffectHandle = ASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), ASC);
	}
}

