#include "raylib.h"

#include <UI/Menu.h>
#include <Input/InputMenu.h>

InputMenu::InputMenu(Menu* gameMenu)
{
	GameMenu = gameMenu;
}

void InputMenu::InputTick(int key)
{
	switch (key)
	{
	case KEY_SPACE:
		GameMenu->SetCorrectIndex(Menu::MenuIndex::MainMenu);
		break;
	default:
		break;
	}
}
