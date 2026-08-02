#pragma once

#include <Core/HUD/HUD.h>

class WCanvasPanel;
class WButton;
class WRichText;

class MenuHUD : public HUD
{
	WCanvasPanel* CanvaPanel;
	WButton* StartButton;
	WRichText* TileText;
	WRichText* SubtitleText;
	WRichText* ExitText;
protected:
	virtual void HUDConstruction() override;
};