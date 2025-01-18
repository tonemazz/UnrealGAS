// Copyright Tone 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"


class UAbilitySystemComponent;
class UAttributeSet;

USTRUCT(BlueprintType) struct FWidgetControllerParams {
	GENERATED_BODY()

	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* InPlayerController, APlayerState* InPlayerState, UAbilitySystemComponent* InAbilitySystemComponent, UAttributeSet* InAttributeSet) 
		: PlayerController(InPlayerController), PlayerState(InPlayerState), AbilitySystemComponent(InAbilitySystemComponent), AttributeSet(InAttributeSet) {}

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController") TObjectPtr<APlayerController> PlayerController = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController") TObjectPtr<APlayerState> PlayerState = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController") TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController") TObjectPtr<UAttributeSet> AttributeSet = nullptr;

};

UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void BindCallbacksToDependencies();
	virtual void BroadcastInitialValues();
UFUNCTION(BlueprintCallable) void SetWidgetControllerParams(const FWidgetControllerParams& InParams);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController") TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController") TObjectPtr<APlayerState> PlayerState;
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController") TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController") TObjectPtr<UAttributeSet> AttributeSet;
};
