
#pragma once
#include "Framework/Commands/Commands.h"
#include "Styling/AppStyle.h"
 
#define LOCTEXT_NAMESPACE "MyCustomCommands"
 
class FMyCustomCommands final : public TCommands<FMyCustomCommands>
{
public:
 
	FMyCustomCommands()
		: TCommands<FMyCustomCommands>(
			// Unique name of the commands set
			"MyCustomCommands",

			// Human readable name (will be displayed in the editor preferences window)
			LOCTEXT("MyCustomCommandsName", "My Custom Commands"),

			// Name of the parent commands set this one is extending (if any)
			NAME_None,

			// Name of the style set from which command icons should be loaded (if any)
			FAppStyle::GetAppStyleSetName()
		)
	{}

	// Commands should be declared as members
	TSharedPtr<FUICommandInfo> MyCustomButton;
	TSharedPtr<FUICommandInfo> MyCustomEntry;

	// RegisterCommands should be overridden to define the commands
	void RegisterCommands() override
	{
		UI_COMMAND
		(
			MyCustomButton,

			// Label
			"My custom button",

			// Tooltip
			"Tooltip for my custom button",

			// UI representation (when used to dynamically build toolbars and menus)
			EUserInterfaceActionType::Button,

			// Default keyboard shortcut (can be empty)
			FInputChord(EKeys::C, EModifierKey::Shift | EModifierKey::Alt)
		);
 
		UI_COMMAND(MyCustomEntry, "My custom entry", "Tooltip for my custom entry", 
			EUserInterfaceActionType::Button, FInputChord());
	}
};
 
#undef LOCTEXT_NAMESPACE
