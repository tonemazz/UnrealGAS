// Copyright Tone 2025

/// <CLASS SUMMARY>
/// - AAuraHUD : public AHUD
/// 
/// - Responsibilities
///		- Manages the HUD for player characters
///		- Creation and initialization of overlay widgets and 
///			the controller that manages them.
/// </CLASS SUMMARY>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;
class UOverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY() TObjectPtr<UAuraUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& InParams);
	void InitializeOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);


protected:
	virtual void BeginPlay() override;

private:
	// Editor linkage pointers
	UPROPERTY(EditAnywhere) TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	UPROPERTY(EditAnywhere) TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

};
