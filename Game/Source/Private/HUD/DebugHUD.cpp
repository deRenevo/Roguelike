// Copyright deRenevo. All rights reserved.

#include "HUD/DebugHUD.h"

#include "Core/Utility/DrawUtility.h"
#include "Core/Widget/Button.h"
#include "Core/Widget/CanvasPanel.h"
#include <string>
#include <iostream>

void DebugHUD::HUDConstruction()
{
	WCanvasPanel* CanvasPanel = new WCanvasPanel();
	SetRootWidget(std::unique_ptr<WWidget>(CanvasPanel));
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
