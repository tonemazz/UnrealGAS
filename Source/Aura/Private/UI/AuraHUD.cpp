// Copyright Tone 2025


#include "UI/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/Widget/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Player/AuraPlayerState.h"



/// <summary>
/// BeginPlay function
/// </summary>
void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}

/// <summary>
/// Initialize the overlay widget and link it to a WidgetController. 
/// Will crash if OverlayWidgetClass or OverlayWidgetControllerClass is not set in the editor.
/// </summary>
void AAuraHUD::InitializeOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not initialized. Please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not initialized. Please fill out BP_AuraHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
}

/// <summary>
/// Create OverlayWidgetController if it doesn't exist, or return the existing one.
/// Necessary due to the fact that we can't create UObject-derived objects in constructor.
/// </summary>
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




