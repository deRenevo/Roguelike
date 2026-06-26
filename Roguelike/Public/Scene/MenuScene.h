#include "raylib.h"

#include <Core/Scene/Scene.h>
#include <vector>
#include <Core/Widgets/WidgetsElements/Button.h>
class MenuHUD;



class MenuScene : public Scene
{

public:
	enum class EMenuState
	{
		None,
		StartMenu,
		MainMenu
	};

	virtual ~MenuScene() override;

private:
	EMenuState MenuState;
	MenuHUD* MenuHud;
	Button* bt;

public:
	void ToMainMenu();

protected:
	virtual void Draw() override;
	virtual void SceneConstruction() override;
	virtual void Tick(float DeltaTick) override;
	virtual void KeyPressEvent(int key) override;
	virtual void Destroy() override;

private:
	void DrawStartMenu();

	void OnCliced();

	//=>Setter and getter
public:
	void SetMenuState(EMenuState state);

	EMenuState GetMenuState() const;
};

