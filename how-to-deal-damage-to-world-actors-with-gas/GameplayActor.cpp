
#include "GameplayActor.h"

#include "Net/Core/PushModel/PushModel.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"

AGameplayActor::AGameplayActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bReplicates = true;
}
 
void AGameplayActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
 
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
 
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, AbilitySystemComponent, SharedParams);
}
 
void AGameplayActor::OnSubobjectCreatedFromReplication(UObject* NewSubObject)
{
	Super::OnSubobjectCreatedFromReplication(NewSubObject);
 
	// Initialize ASC immediately as it is created (OnRep would be called too late)
	if (AbilitySystemComponent == nullptr)
	{
		AbilitySystemComponent = Cast<UAbilitySystemComponent>(NewSubObject);
		if (AbilitySystemComponent != nullptr)
		{
			AbilitySystemInitialized();
		}
	}
}
 
void AGameplayActor::InitializeAbilitySystem()
{
	if (!ensure(HasAuthority()) || AbilitySystemComponent != nullptr)
	{
		// Don't initialize twice or on clients
		return;
	}
 
	AbilitySystemComponent = NewObject<UAbilitySystemComponent>(this);
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AbilitySystemComponent->RegisterComponent();
	MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, AbilitySystemComponent, this);
 
	// Attribute set (i.e. containing the Health attribute) can be initialized here
	// Startup gameplay effects can be applied here too
 
	AbilitySystemInitialized();
}
 
void AGameplayActor::AbilitySystemInitialized()
{
	check(AbilitySystemComponent != nullptr);
	if (!HasAuthority())
	{
		// This is done automatically on the server when the component is registered
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}
