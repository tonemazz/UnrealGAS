// Copyright Tone 2025
// The naive implementation of accessing and modifying attributes
// To be replaced with Gameplay Effects implementation

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
UENUM(BlueprintType) enum EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

class UGameplayEffect;
UENUM(BlueprintType) enum EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();
	virtual void Tick(float DeltaTime) override;

	// Callback to OnComponentBeginOverlap
// Currently implemented in blueprint	// UFUNCTION() virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Callback to OnComponentEndOverlap
//	UFUNCTION() virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

		UFUNCTION(BlueprintCallable) void OnOverlap(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
		UFUNCTION(BlueprintCallable) void OnEndOverlap(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UFUNCTION(BlueprintCallable) void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects") TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;\
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects") TEnumAsByte<EEffectApplicationPolicy> InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects") TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects") TEnumAsByte<EEffectApplicationPolicy> DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects") TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects") TEnumAsByte<EEffectApplicationPolicy> InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects") TEnumAsByte<EEffectRemovalPolicy> InfiniteEffectRemovalPolicy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bDestroyOnEffectRemoval = false;
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
private:

	UPROPERTY(EditAnywhere) float HealthAddAmount = 50.f;
	UPROPERTY(EditAnywhere) float ManaAddAmount = -25.f;
	UPROPERTY(EditAnywhere) bool bConsumable = false;

};
