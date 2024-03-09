
#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "MyDestructible.h"
#include "WorldFixture.h"

BEGIN_DEFINE_SPEC(FMyDestructibleSpec, "MyDestructible",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

TUniquePtr<FWorldFixture> WorldFixture;
TWeakObjectPtr<AMyDestructible> DestructibleFixture;

END_DEFINE_SPEC(FExampleSpec);

void FExampleSpec::Define()
{
	Describe("AMyDestructible", [this]()
	{
		BeforeEach([this]()
		{
			// Create the world
			WorldFixture = MakeUnique<FWorldFixture>();

			if (TestNotNull("World", WorldFixture->GetWorld()))
			{
				// Spawn the actor
				DestructibleFixture = WorldFixture->GetWorld()->SpawnActor<AMyDestructible>();
				TestNotNull("MyDestructible", DestructibleFixture.Get());
			}
		});

		AfterEach([this]()
		{
			// Tear down the world and the actor
			WorldFixture.Reset();
		});

		It("Should not explode when dealt zero damage", [this]()
		{
			MyDestructible->Damage(0.0);
			TestFalse("HasExploded", MyDestructible->HasExploded());
		});

		It("Should explode when dealt damage", [this]()
		{
			MyDestructible->Damage(1.0);
			TestTrue("HasExploded", MyDestructible->HasExploded());
		});
	});
}

#endif
