
#include "MyActor.h"
#include "Components/StaticMeshComponent.h"

AMyActor::AMyActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
}
