
class InputMenu;
class Button;

class Menu
{

public:
	enum MenuIndex : int
	{
		NONE,
		StartMenu,
		MainMenu
	};

private:
	MenuIndex CorrectIndex;

	InputMenu* InputMenuComp;
	Button* StartGameButton;

public:
	Menu();
	~Menu();

public:
	void Update();
	void InputTick(int key);
	void SetCorrectIndex(MenuIndex index);
private:
	void Draw();
	void DrawStartMenu();
	void DrawMainMenu();
};