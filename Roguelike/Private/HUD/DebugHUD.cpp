#include <HUD/DebugHUD.h>

#include <Core/Utility/Draw/DrawUtility.h>
#include <Core/Widgets/WidgetsElements/Button.h>
#include <Core/Widgets/WidgetsElements/CanvasPanel.h>
#include <string>
#include <iostream>

void DebugHUD::HUDConstruction()
{
	CanvasPanel* panel = new CanvasPanel();
	SetRootWidget(panel);
}

void DebugHUD::Draw()
{
	HUD::Draw();
	DrawUtility::DrawTextWithTwoColor(
		std::string("FPS: " + std::to_string(GetFPS())).c_str(),
		15,
		50,
		{1},
		20,
		RAYWHITE,
		GREEN);
}

void DebugHUD::Tick(float DeltaTime)
{
	HUD::Tick(DeltaTime);
}
