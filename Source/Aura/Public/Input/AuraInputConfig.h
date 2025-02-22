// Copyright Tone 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfig.generated.h"


USTRUCT(BlueprintType) struct FAuraInputAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();

};
/**
 * 
 */
UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag InputTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FAuraInputAction> InputActions;
	
};
