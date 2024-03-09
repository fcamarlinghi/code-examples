
#pragma once
#include "Modules/ModuleManager.h"
#include "ToolMenus.h"
 
class FMyEditorModule final : public IModuleInterface
{
public:
 
	void StartupModule() override
	{
		// Register a function to be called when menu system is initialized
		UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(
			this, &FMyEditorModule::RegisterMenuExtensions));
	}
 
	void ShutdownModule() override
	{
		// Unregister the startup function
		UToolMenus::UnRegisterStartupCallback(this);

		// Unregister all our menu extensions
		UToolMenus::UnregisterOwner(this);
	}
 
private:
 
	void RegisterMenuExtensions()
	{
		// Use the current object as the owner of the menus
		// This allows us to remove all our custom menus when the 
		// module is unloaded (see ShutdownModule below)
		FToolMenuOwnerScoped OwnerScoped(this);

		// Extend the "File" section of the main toolbar
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu(
			"LevelEditor.LevelEditorToolBar.ModesToolBar");
		FToolMenuSection& ToolbarSection = ToolbarMenu->FindOrAddSection("File");
 
		ToolbarSection.AddEntry(FToolMenuEntry::InitToolBarButton(
			TEXT("MyCustomButtonName"),
			FExecuteAction::CreateLambda([]()
			{
				// Simply log for this example
				UE_LOG(LogTemp, Log, TEXT("MyCustomButton triggered!!"));
			}),
			INVTEXT("My custom button"),
			INVTEXT("Tooltip for my custom button"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Comment")
		));

		// Add a new section to the Select menu right after the "BSP" section
		UToolMenu* SelectionMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Select");
		FToolMenuSection& SelectionSection = SelectionMenu->AddSection(
			"MyCustomSection",
			INVTEXT("My Custom Section"),
			FToolMenuInsert("SelectBSP", EToolMenuInsertType::After)
		);
 
		SelectionSection.AddEntry(FToolMenuEntry::InitMenuEntry(
			"MyCustomEntryName",
			INVTEXT("My custom entry"),
			INVTEXT("Tooltip for my custom entry"),
			FSlateIcon(),
			FExecuteAction::CreateLambda([]()
			{
				// Simply log for this example
				UE_LOG(LogTemp, Log, TEXT("MyCustomEntry triggered!!"));
			})
		));
	}
};
 
IMPLEMENT_MODULE(FMyEditorModule, MyEditorModule)
