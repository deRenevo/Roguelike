class Menu;

class InputMenu
{
	Menu* GameMenu;

public:
	InputMenu(Menu* gameMenu);

	void InputTick(int key);
};