#include <Core/HUD/HUD.h>

void HUD::OnEnter()
{
	PreHUDConstruction();
	HUDConstruction();
	PostHUDConstruction();
}

void HUD::OnExit()
{
}

void HUD::Tick(float DeltaTime)
{
}

void HUD::Draw()
{
}

void HUD::KeyPressEvent(int key)
{
}

void HUD::HUDConstruction()
{
}

void HUD::PreHUDConstruction()
{
}

void HUD::PostHUDConstruction()
{
}
