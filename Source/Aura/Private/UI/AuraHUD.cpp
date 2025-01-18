// Copyright Tone 2025

/// <CLASS SUMMARY>
/// - AAuraHUD : public AHUD
/// 
/// - Responsibilities
///		- Manages the HUD for player characters
///		- Creation and initialization of overlay widgets and 
///			the controller that manages them.
/// </CLASS SUMMARY>

#include "UI/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/Widget/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Player/AuraPlayerState.h"


/// <function summary>
///	It's the first function called when the game starts.
/// </function summary>
void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}

/// <function summary>
/// Initialize the overlay widget and link it to a WidgetController. 
/// Will crash if OverlayWidgetClass or OverlayWidgetControllerClass is not set in the editor.
/// WARNING: This function should be after all its parameters are initialized.
/// This is currently done from the AuraCharacter class.
/// </function summary>
void AAuraHUD::InitializeOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not initialized. Please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not initialized. Please fill out BP_AuraHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);

	Widget->AddToViewport();
}

/// <function summary>
/// Returns the OverlayWidgetController. If it doesn't exist, it creates a new one.
/// </function summary>
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& InParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(InParams);

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}




