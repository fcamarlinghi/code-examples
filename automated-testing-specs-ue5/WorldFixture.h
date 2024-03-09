
#pragma once

#if WITH_AUTOMATION_TESTS

#include "GameFramework/WorldSettings.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Engine/EngineBaseTypes.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "EngineUtils.h"

class FWorldFixture final
{
public:

	explicit FWorldFixture(const FURL& URL = FURL())
	{
		if (GEngine != nullptr)
		{
			static uint32 WorldCounter = 0;
			const FString WorldName = FString::Printf(TEXT("WorldFixture_%d"), WorldCounter++);

			if (UWorld* World = UWorld::CreateWorld(EWorldType::Game, false, *WorldName, GetTransientPackage()))
			{
				FWorldContext& WorldContext = GEngine->CreateNewWorldContext(EWorldType::Game);
				WorldContext.SetCurrentWorld(World);

				World->InitializeActorsForPlay(URL);
				if (IsValid(World->GetWorldSettings()))
				{
					// Need to do this manually since world doesn't have a game mode
					World->GetWorldSettings()->NotifyBeginPlay();
					World->GetWorldSettings()->NotifyMatchStarted();
				}
				World->BeginPlay();

				WeakWorld = MakeWeakObjectPtr(World);
			}
		}
	}

	UWorld* GetWorld() const { return WeakWorld.Get(); }

	~FWorldFixture()
	{
		UWorld* World = WeakWorld.Get();
		if (World != nullptr && GEngine != nullptr)
		{
			World->BeginTearingDown();

			// Make sure to cleanup all actors immediately
			// DestroyWorld doesn't do this and instead waits for GC to clear everything up
			for (auto It = TActorIterator<AActor>(World); It; ++It)
			{
				It->Destroy();
			}

			GEngine->DestroyWorldContext(World);
			World->DestroyWorld(false);
		}
	}

private:

	TWeakObjectPtr<UWorld> WeakWorld;
};

#endif
