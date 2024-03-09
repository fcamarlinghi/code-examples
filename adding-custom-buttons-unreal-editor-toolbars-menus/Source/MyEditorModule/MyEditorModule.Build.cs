
using UnrealBuildTool;

public class MyEditorModule : ModuleRules
{
	public MyEditorModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivateIncludePaths.Add("MyEditorModule");

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"Slate",
			"SlateCore",
			"ToolMenus",
		});
	}
}
