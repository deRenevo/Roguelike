// Copyright deRenevo. All rights reserved.

#include "Core/HUD/HUD.h"


void HUD::DoTick(float deltaTime)
{
	if (!bIsVisible) return;

	Tick(deltaTime);
}

void HUD::DoDraw()
{
	if (!bIsVisible) return;

	Draw();
}

void HUD::OnEnter()
{
	if (bIsInitialized) return;
	bIsInitialized = true;
	PreHUDConstruction();
	HUDConstruction();
	PostHUDConstruction();
}

void HUD::OnExit()
{
}

void HUD::Tick(float deltaTime)
{
	if (RootWidget && RootWidget->GetVisible())
	{
		RootWidget->DoTick(deltaTime);
	}
}

void HUD::Draw()
{
	if (RootWidget && RootWidget->GetVisible())
	{
		RootWidget->DoDraw();
	}
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

void HUD::SetRootWidget(std::unique_ptr<WWidget> rootWidget)
{
	if (!rootWidget)
	{
		return;
	}

	RootWidget.swap(rootWidget);
	RootWidget->OnEnter();
}
