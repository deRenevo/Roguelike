#include <Core/HUD/HUD.h>

#include <iostream>

void HUD::DoTick(float DeltaTime)
{
	if (!bIsVisible) return;

	Tick(DeltaTime);
}

void HUD::DoDraw()
{
	if (!bIsVisible) return;

	Draw();
}

void HUD::OnEnter()
{
	std::cout << "HUD | OnEnter" << std::endl;
	if (bIsInitialized) return;
	bIsInitialized = true;
	PreHUDConstruction();
	HUDConstruction();
	PostHUDConstruction();
}

void HUD::OnExit()
{
}

void HUD::Tick(float DeltaTime)
{
	if (RootWidget && RootWidget->GetVisible())
	{
		RootWidget->DoTick(DeltaTime);
	}
}

void HUD::Draw()
{
	if (RootWidget && RootWidget->GetVisible())
	{
		RootWidget->DoDraw();
	}
}

void HUD::KeyPressEvent(int key)
{
}

void HUD::HUDConstruction()
{
	std::cout << "HUDConstruction" << std::endl;
}

void HUD::PreHUDConstruction()
{
}

void HUD::PostHUDConstruction()
{
}

void HUD::SetRootWidget(Widget* rootWidget)
{
	std::cout << "SetRootWidget";

	if (!rootWidget)
	{
		return;
	}

	RootWidget.reset(rootWidget);
	RootWidget->OnEnter();
}

void HUD::SetIsVisible(bool isVisible)
{
	bIsVisible = isVisible;
}

Widget* HUD::GetRootWidget()
{
	return RootWidget.get();
}

bool HUD::GetIsVisible()
{
	return bIsVisible;
}