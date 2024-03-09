
#pragma once
#include "GameFramework/Actor.h"
#include "MyDestructible.generated.h"

UCLASS()
class AMyDestructible : public AActor
{
	GENERATED_BODY()

private:

	bool bExploded = false;

public:

	void Damage(float DamageAmount)
	{
		if (DamageAmount > 0.0f)
		{
			bExploded = true;
		}
	}

	bool HasExploded() const { return bExploded; }
};
