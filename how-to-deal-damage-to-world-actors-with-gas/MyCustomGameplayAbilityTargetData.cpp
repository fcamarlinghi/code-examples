
#include "GameplayActor.h"
#include "MyCustomGameplayAbilityTargetData.h"

TArray<FActiveGameplayEffectHandle> FMyCustomGameplayAbilityTargetData::ApplyGameplayEffectSpec(
	FGameplayEffectSpec& Spec, const FPredictionKey PredictionKey)
{
	// Activate gameplay actors
	for (const TWeakObjectPtr<AActor>& TargetActor : GetActors())
	{
		AGameplayActor* GameplayActor = Cast<AGameplayActor>(TargetActor);
		if (GameplayActor != nullptr && GameplayActor->AbilitySystemComponent == nullptr)
		{
			GameplayActor->InitializeAbilitySystem();
		}
	}
 
	return FGameplayAbilityTargetData::ApplyGameplayEffectSpec(Spec, PredictionKey);
}

UScriptStruct* FMyCustomGameplayAbilityTargetData::GetScriptStruct() const
{
	return StaticStruct();
}
