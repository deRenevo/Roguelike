#include <Core/HUD/HUD.h>

class CanvasPanel;
class Button;

class MenuHUD : public HUD
{
	CanvasPanel* CanvaPanel;
	Button* StartButton;
protected:
	virtual void HUDConstruction() override;
	virtual void Draw() override;
};