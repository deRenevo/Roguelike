#include "raylib.h"

#include <Core/HUD/HUD.h>

class DebugHUD : public HUD
{
	virtual void Draw() override;
	virtual void Tick(float DeltaTime) override;
};

