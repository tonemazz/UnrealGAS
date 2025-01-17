// Copyright Tone 2025
// The naive implementation of accessing and modifying attributes
// To be replaced with Gameplay Effects implementation

#include "Actor/AuraEffectActor.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);

	// Setup for highlighting functionality
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Mesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	// Bind callbacks to delegates
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Cast to check if OtherActor implements IAbilitySystemInterface
	IAbilitySystemInterface* OtherActorASCInterface = Cast<IAbilitySystemInterface>(OtherActor);

	if (OtherActorASCInterface)
	{
		// Currently forsaking encapsulation and using const_cast for testing purposes;
		// TODO: Implement attribute modification through Gameplay Effects (the GAS intended way)
		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(OtherActorASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		UAuraAttributeSet* MutableAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);

		// While this will work, it bypasses the GAS's network replication
		MutableAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + HealthAddAmount);
	}

	if (bConsumable)
	{
		Destroy();
	}
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AAuraEffectActor::HighlightActor()
{
	Mesh->SetRenderCustomDepth(true);
	UE_LOG(LogTemp, Warning, TEXT("Highlighting actor"));
}

void AAuraEffectActor::UnHighlightActor()
{
	Mesh->SetRenderCustomDepth(false);
	UE_LOG(LogTemp, Warning, TEXT("Un-Highlighting actor"));
}

