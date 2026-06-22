#include "raylib.h"

#include <Utility/Draw/DrawUtility.h>
#include <Input/InputMenu.h>
#include <UI/Widgets/Button.h>
#include <UI/Menu.h>

Menu::Menu() : CorrectIndex(MenuIndex::StartMenu)
{
	InputMenuComp = new InputMenu(this);
	StartGameButton = new Button("Start",
		Rectangle(GetScreenWidth() / 2,
			GetScreenHeight() / 2, 200, 80),
		24, RAYWHITE, GRAY, DARKGRAY, 2.0, true);
}

Menu::~Menu()
{
}

void Menu::Update()
{
	Draw();
}

void Menu::InputTick(int key)
{
	InputMenuComp->InputTick(key);
}

void Menu::Draw()
{
	switch (CorrectIndex)
	{
	case Menu::NONE:
		return;
	case Menu::StartMenu:
		DrawStartMenu();
		break;
	case Menu::MainMenu:
		DrawMainMenu();
		break;
	default:
		break;
	}
}

void Menu::DrawStartMenu()
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
		{ 1 },
		AdditionFontSize,
		RAYWHITE,
		SKYBLUE,
		true);

	DrawUtility::DrawTextWithTwoColor(
		"ESC - EXIT",
		16,
		16,
		{ 2 },
		20,
		RAYWHITE,
		SKYBLUE);
}

void Menu::DrawMainMenu()
{
	StartGameButton->Update();

	DrawUtility::DrawTextWithTwoColor(
		"ESC - EXIT",
		16,
		16,
		{ 2 },
		20,
		RAYWHITE,
		SKYBLUE);
}


/*
* >> setter and getter
*/

void Menu::SetCorrectIndex(MenuIndex index)
{
	CorrectIndex = index;
}
