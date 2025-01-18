// Copyright Tone 2025

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/WidgetController/AuraWidgetController.h"
#include "Delegates/DelegateCombinations.h"
#include "OverlayWidgetController.generated.h"


struct FOnAttributeChangeData;
/// Dynamic MultiCast Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")FOnMaxHealthChangedSignature OnMaxHealthChanged;

	protected:
 void HealthChanged(const FOnAttributeChangeData& Data) const;
	static void MaxHealthChanged(const FOnAttributeChangeData& Data);
	
};
