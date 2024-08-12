
#pragma once
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "MyCustomGameplayAbilityTargetData.generated.h"

USTRUCT()
struct FMyCustomGameplayAbilityTargetData : public FGameplayAbilityTargetData
{
	GENERATED_BODY()

	// FGameplayAbilityTargetData interface
public:
	TArray<FActiveGameplayEffectHandle> ApplyGameplayEffectSpec(FGameplayEffectSpec& Spec,
		FPredictionKey PredictionKey = FPredictionKey()) override;
	UScriptStruct* GetScriptStruct() const override;
};

template<>
struct TStructOpsTypeTraits<FMyCustomGameplayAbilityTargetData> 
	: public TStructOpsTypeTraitsBase2<FMyCustomGameplayAbilityTargetData>
{
	enum { WithNetSerializer = true };
};
