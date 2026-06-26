#include <HUD/MenuHUD.h>
#include <Core/Widgets/WidgetsElements/CanvasPanel.h>
#include <Core/Widgets/WidgetsElements/Button.h>
#include <memory>
#include <iostream>


void MenuHUD::HUDConstruction()
{
	CanvaPanel = new CanvasPanel();
	SetRootWidget(CanvaPanel);

	StartButton = new Button("Start", Rectangle(100, 200, 100, 200));
	StartButton->SetWorldLocation(Vector2{ 100, 200 });
	StartButton->SetOnClick([this]() {
		std::cout << "Start clicked!\n";
		});

	CanvaPanel->AddChild(std::unique_ptr<Widget>(StartButton));
}

void MenuHUD::Draw()
{
	HUD::Draw();
	//if (StartButton) StartButton->DoDraw();
}
