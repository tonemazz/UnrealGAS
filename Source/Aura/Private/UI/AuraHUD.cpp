// Copyright Tone 2025

/**
 * @file AuraHUD.cpp
 * @brief Implementation of the AAuraHUD class.
 *
 * AAuraHUD manages the HUD for player characters, including the creation and initialization
 * of overlay widgets and their controllers.
 *
 * Responsibilities:
 *  - Manage the HUD for player characters.
 *  - Create and initialize overlay widgets and the controller that manages them.
 */

#include "UI/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/Widget/WidgetController/OverlayWidgetController.h"

/**
 * @brief Called when the game starts.
 *
 * This function is the first to be called when the game begins. It creates an instance
 * of the overlay widget and adds it to the viewport.
 */
void AAuraHUD::BeginPlay()
{
    Super::BeginPlay();

    // Create the overlay widget using the class specified in OverlayWidgetClass
    UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
    // Add the created widget to the viewport to make it visible.
    Widget->AddToViewport();
}

/**
 * @brief Initializes the overlay widget and links it to its widget controller.
 *
 * This function creates and initializes the overlay widget and its controller. It will crash
 * if either OverlayWidgetClass or OverlayWidgetControllerClass is not set in the editor.
 * 
 * @warning This function should be called only after all required parameters are initialized.
 *          Currently, it is invoked from the AuraCharacter class once the parameters have been set.
 *
 * @param PC A pointer to the player's controller.
 * @param PS A pointer to the player's state.
 * @param ASC A pointer to the ability system component.
 * @param AS A pointer to the attribute set.
 */
void AAuraHUD::InitializeOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
    // Ensure the necessary widget classes are set in the editor.
    checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not initialized. Please fill out BP_AuraHUD"));
    checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not initialized. Please fill out BP_AuraHUD"));

    // Create the overlay widget.
    UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
    // Cast the widget to UAuraUserWidget to access specific functionality.
    OverlayWidget = Cast<UAuraUserWidget>(Widget);

    // Initialize widget controller parameters.
    const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
    // Retrieve (or create) the overlay widget controller using the provided parameters.
    UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
    
    // Link the widget with its controller.
    OverlayWidget->SetWidgetController(WidgetController);
    // Broadcast initial values so the UI can update immediately.
    WidgetController->BroadcastInitialValues();
    // Add the overlay widget to the viewport.
    Widget->AddToViewport();
}

/**
 * @brief Retrieves the Attribute Menu Widget Controller.
 *
 * If the AttributeMenuWidgetController does not exist, this function creates a new one,
 * sets its parameters, and binds necessary callbacks.
 *
 * @param InParams The parameters required to configure the widget controller.
 * @return A pointer to the UAttributeMenuWidgetController instance.
 */
UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& InParams)
{
    if (AttributeMenuWidgetController == nullptr)
    {
        // Create a new Attribute Menu Widget Controller using the specified class.
        AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
        // Set up the controller with the required parameters.
        AttributeMenuWidgetController->SetWidgetControllerParams(InParams);
        // Bind any necessary callbacks to the controller's dependencies.
        AttributeMenuWidgetController->BindCallbacksToDependencies();
    }
    return AttributeMenuWidgetController;
}

/**
 * @brief Retrieves the Overlay Widget Controller.
 *
 * If the OverlayWidgetController does not exist, this function creates a new one,
 * sets its parameters, and binds necessary callbacks.
 *
 * @param InParams The parameters required to configure the widget controller.
 * @return A pointer to the UOverlayWidgetController instance.
 */
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& InParams)
{
    if (OverlayWidgetController == nullptr)
    {
        // Create a new Overlay Widget Controller using the specified class.
        OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
        // Set up the controller with the required parameters.
        OverlayWidgetController->SetWidgetControllerParams(InParams);
        // Bind any necessary callbacks to the controller's dependencies.
        OverlayWidgetController->BindCallbacksToDependencies();
    }
    return OverlayWidgetController;
}
