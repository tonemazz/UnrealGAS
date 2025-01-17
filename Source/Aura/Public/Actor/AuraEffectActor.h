// Copyright Tone 2025
// The naive implementation of accessing and modifying attributes
// To be replaced with Gameplay Effects implementation

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEffectActor.generated.h"



UCLASS()
class AURA_API AAuraEffectActor : public AActor, public IEnemyInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();
	virtual void Tick(float DeltaTime) override;

	// Callback to OnComponentBeginOverlap
	UFUNCTION() virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Callback to OnComponentEndOverlap
	UFUNCTION() virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere) TObjectPtr<USphereComponent> Sphere;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere) float HealthAddAmount = 50.f;
	UPROPERTY(EditAnywhere) bool bConsumable = false;
};
