#pragma once

#include <Core/HUD/HUD.h>

class WButton;

class DebugHUD : public HUD
{
	WButton* GoodButton;
protected:
	virtual void HUDConstruction() override;
	virtual void Draw() override;
	virtual void Tick(float DeltaTime) override;
};

