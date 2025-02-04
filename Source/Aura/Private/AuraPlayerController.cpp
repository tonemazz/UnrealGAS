// Tone


#include "AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// Asserts that the AuraContext is valid, crash otherwise
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem) 
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}


	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;

	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); 	// Do not lock the mouse to the viewport
	InputModeData.SetHideCursorDuringCapture(false); // Do not hide the cursor during capture
	SetInputMode(InputModeData);

}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);

} // end of SetupInputComponent()

void AAuraPlayerController::CursorTrace()
{
	

	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit) return;

	Cast<IEnemyInterface>(CursorHit.GetActor()); // Implementation check

	LastActor = CurrentActor;
	CurrentActor = CursorHit.GetActor();



	/* 
		Line trace from cursor. Several scenarios:
		A. LastActor is null and CurrentActor is null
			- Do nothing
		B. LastActor is null and CurrentActor is valid (Getting valid actor for first time)
			- Highlight CurrentActor
		C. LastActor is valid and CurrentActor is null (No longer hovering over a valid actor)
			- UnHighlight LastActor
		D. Both actors are valid, but LastActor != CurrentActor (We are hovering over a different valid actor than the previous)
			- UnHilight LastActor  and Highlight CurrentActor
		E. Both actors are valid, and the same actor
			- Do nothing
	*/

	if (LastActor == nullptr)
	{
		if (CurrentActor != nullptr)
		{
			// Case B
			CurrentActor->HighlightActor();
		}
		else
		{
			// Both null, do nothing (Case A)
		}
	}
	else // LastActor is valid
	{
		if (CurrentActor == nullptr)
		{
			// Case C
			LastActor->UnHighlightActor();
		}
		else // Both actors are valid 
		{
			if (LastActor != CurrentActor) // Case D
			{
				LastActor->UnHighlightActor();
				CurrentActor->HighlightActor();
			}
			else 
			{
				// Case E, do nothing
			}
		}
	}

} // end of CursorTrace()

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0); // For purposes of ground character movement, we are only concerned with the horizontal rotation, as factoring in X or Z rotation would make us try out of the plane of the ground
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // Our forward facing leveled to the horizon
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // Our right direction leveled to the horizon
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y); // InputAxisVector should return 1 when pressing W or forward stick, and -1 when pressing S or backward 
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
} // end of Move()
