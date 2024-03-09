
#pragma once
#include "GameFramework/Actor.h"
#include "GameplayActor.generated.h"

class UAbilitySystemComponent;

/**
 * Base class for world actors that need to tap into the 
 * ability system, such as destructible items, etc.
 */
UCLASS(Abstract)
class AGameplayActor : public AActor
{
	GENERATED_BODY()
 
public:
 
	AGameplayActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
 
	UPROPERTY(Transient, Replicated)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
 
	/** Initializes the ability system component. */
	void InitializeAbilitySystem();
 
protected:
 
	/** Called on authority and clients when the ability system component is initialized. */
	virtual void AbilitySystemInitialized();
 
	// AActor interface
public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void OnSubobjectCreatedFromReplication(UObject* NewSubObject) override;
};
