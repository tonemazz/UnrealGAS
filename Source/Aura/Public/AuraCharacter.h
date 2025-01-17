// Tone

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class AAuraPlayerState;

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	virtual void BeginPlay() override;
	TObjectPtr<AAuraPlayerState> PlayerState;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
};
