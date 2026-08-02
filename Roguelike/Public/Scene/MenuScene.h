#include "raylib.h"

#include <Core/Scene/Scene.h>
#include <vector>

class MenuHUD;
class WButton;



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
	WButton* bt;

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
	
public:
	void SetMenuState(EMenuState state);

	EMenuState GetMenuState() const;
};

