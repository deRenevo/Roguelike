#include "raylib.h"

#include <Core/Utility/Draw/DrawUtility.h>
#include <Core/Widgets/WidgetsElements/Button.h>
#include <Scene/MenuScene.h>
#include <Core/Scene/SceneManager.h>
#include <HUD/MenuHUD.h>
#include <Roguelike.h>
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <functional>

void MenuScene::SceneConstruction()
{
	Scene::SceneConstruction();
	MenuState = EMenuState::StartMenu;
	auto hud = std::make_unique<MenuHUD>();
	MenuHud = hud.get();
	SceneManager::GetInstance().AddToViewport(std::move(hud));
}

void MenuScene::Tick(float DeltaTick)
{
}

void MenuScene::KeyPressEvent(int key)
{
	switch (key)
	{
	case KEY_SPACE:
		if (MenuState == EMenuState::StartMenu)
		{
			ToMainMenu();
		}
		break;

	case KEY_ESCAPE:
		Roguelike::GetInstance().Stop();
		break;
	default:
		break;
	}
}

void MenuScene::Destroy()
{
	if (MenuHud)
	{
		SceneManager::GetInstance().RemoveHUD(MenuHud);
	}
}

MenuScene::~MenuScene()
{
	
}

void MenuScene::Draw()
{
	DrawStartMenu();

}

void MenuScene::DrawStartMenu()
{
	
	const char* Title = "Roguelike";
	const int FontSize = 48;
	const int TextWidth = MeasureText(Title, FontSize);


	const char* AdditionTitle = "Press space to open the menu";
	const int AdditionFontSize = 24;
	const int AdditionTextWidth = MeasureText(AdditionTitle, AdditionFontSize);

	DrawText(
		Title,
		(GetScreenWidth() - TextWidth) / 2,
		GetScreenHeight() / 2 - FontSize / 2,
		FontSize,
		RAYWHITE);

	DrawUtility::DrawTextWithTwoColor(
		AdditionTitle,
		GetScreenWidth() / 2,
		GetScreenHeight() / 2 + FontSize,
		{1},
		AdditionFontSize,
		RAYWHITE,
		SKYBLUE,
		true);

	DrawUtility::DrawTextWithTwoColor(
		"ESC - EXIT",
		16,
		16,
		{2},
		20,
		RAYWHITE,
		SKYBLUE);
}

void MenuScene::OnCliced()
{
	std::cout << "hi" << std::endl;
}

void MenuScene::ToMainMenu()
{
	SetMenuState(EMenuState::MainMenu);
}



/*
 * -> getter and setter
*/

void MenuScene::SetMenuState(EMenuState state)
{
	MenuState = state;
}

MenuScene::EMenuState MenuScene::GetMenuState() const
{
	return MenuState;
}
