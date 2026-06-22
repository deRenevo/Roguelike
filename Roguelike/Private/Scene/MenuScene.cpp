#include "raylib.h"

#include <Core/Utility/Draw/DrawUtility.h>
#include <Scene/MenuScene.h>
#include <vector>


void MenuScene::Draw()
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