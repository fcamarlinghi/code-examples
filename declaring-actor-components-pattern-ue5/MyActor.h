
#pragma once
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class AMyActor : public AActor
{
	GENERATED_BODY()

public:

	AMyActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintGetter)
	UStaticMeshComponent* GetMeshComponent() const { return MeshComponent; }

private:

	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetMeshComponent, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
};
