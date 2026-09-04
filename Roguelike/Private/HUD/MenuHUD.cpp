// Copyright deRenevo. All rights reserved.

#include "HUD/MenuHUD.h"
#include "Core/Widgets/WidgetsElements/CanvasPanel.h"
#include "Core/Widgets/WidgetsElements/Button.h"
#include "Core/Widgets/WidgetsElements/RichText.h"
#include <memory>
#include <iostream>


void MenuHUD::HUDConstruction()
{
	WCanvasPanel* CanvasPanel = new WCanvasPanel();
	SetRootWidget(std::unique_ptr<WWidget>(CanvasPanel));


	const int ScreenW = GetScreenWidth();
	const int ScreenH = GetScreenHeight();
	{
		std::string TitleRich =
			"[Size=50][Color=RAYWHITE]Roguelike[/Color][/Size]\n[Size=24]Press [Color=SKYBLUE][Size=28]SPACE[Size=24][/Color] to open the menu[/Size]";

		Vector2 TitlePos =
		{
			(float)ScreenW / 2.0f,
			(float)ScreenH / 2.0f
		};

		FRichTextStyle Style;
		Style.VerticalAlignment = EWidgetVerticalAlignment::Center;
		Style.HorizontalAlignment = EWidgetHorizontalAlignment::Center;

		WRichText* TileText = new WRichText(TitleRich, TitlePos, Style);
		TileText->SetAutoSize(true);


		FWidgetStyle WidgetStyle;
		WidgetStyle.WidgetHorizontalAlignment = EWidgetHorizontalAlignment::Center;
		WidgetStyle.WidgetVerticalAlignment = EWidgetVerticalAlignment::Center;
		TileText->SetWidgetStyle(WidgetStyle);
		CanvasPanel->AddChild(std::unique_ptr<WWidget>(TileText));
	}

	{
		std::string ExitHintRich =
			"[Size=20][Color=SKYBLUE]ESC[/Color] - EXIT[/Size]";

		Vector2 ExitHintPos = {
			16.0f,
			16.0f
		};

		WRichText* ExitText = new WRichText(ExitHintRich, ExitHintPos);

		CanvasPanel->AddChild(std::unique_ptr<WWidget>(ExitText));
	}

	{
		WButton* StartButton = new WButton("Start", Rectangle(ScreenW / 2, ScreenH / 2, 100, 200));

		FWidgetStyle WidgetStyle;
		WidgetStyle.WidgetHorizontalAlignment = EWidgetHorizontalAlignment::Center;
		WidgetStyle.WidgetVerticalAlignment = EWidgetVerticalAlignment::Center;

		StartButton->SetWidgetStyle(WidgetStyle);
		StartButton->SetOnClick([this]()
		{
			std::cout << "Start clicked!\n";
		});

		CanvasPanel->AddChild(std::unique_ptr<WWidget>(StartButton));
		StartButton->SetVisible(false);
	}
}
