// Tone


#include "AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include <AuraPlayerController.h>
#include <UI/AuraHUD.h>

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	
}

/// <summary>
/// </summary>
void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
}

/// <summary>
/// </summary>
void AAuraCharacter::PossessedBy(AController* NewController)
{
	// Init ability actor info for the server
	Super::PossessedBy(NewController);
	SetupAbilityActorInfo();
}

/// <summary>
/// </summary>
void AAuraCharacter::OnRep_PlayerState()
{
	// Init ability actor info for the client
	Super::OnRep_PlayerState();
	SetupAbilityActorInfo();
}

/// <summary>
/// Initialize the ability actor info for the player state
/// Also centralizes initialization of AuraHUD parts
/// </summary>
void AAuraCharacter::SetupAbilityActorInfo()
{
	TObjectPtr<AAuraPlayerState> AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	// Call InitializeOverlay Here
	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{ 
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitializeOverlay(AuraPlayerController, AuraPlayerState, AuraPlayerState->GetAbilitySystemComponent(), AuraPlayerState->GetAttributeSet());
		}
	}

}
