// Copyright deRenevo. All rights reserved.

#include "raylib.h"

#include <Core/Utility/Draw/DrawUtility.h>
#include <Core/Widgets/WidgetsElements/Button.h>
#include <Scene/MenuScene.h>
#include <Core/Scene/SceneManager.h>
#include <HUD/MenuHUD.h>
#include <Core/Scene/SceneManager.h>
#include <Core/Actor/PlayerStart.h>

#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <functional>

void MenuScene::SceneConstruction()
{
	SetGameMode(std::make_unique<OTestGameMode>([this](void) { return new ATestPawn();}));
	APlayerStart* PlayerStart = new APlayerStart(Vector2(960, 540));
	AddActorToScene(std::unique_ptr<APlayerStart>(PlayerStart));

	Scene::SceneConstruction();
	SceneManager::GetInstance().AddToViewport(std::move(std::unique_ptr<MenuHUD>(new MenuHUD())));

	for (int i = -20; i < 100; ++i)	
	{
		ATestActor* TestActor = new ATestActor();
		if (i % 2 == 0)
		{
			TestActor->Col = LIME;
		}
		TestActor->SetActorLocation(Vector2(i * 50, 1000));

		AddActorToScene(std::unique_ptr<AActor>(TestActor));
	}
}

void MenuScene::Tick(float DeltaTick)
{
	Scene::Tick(DeltaTick);
}

void MenuScene::Destroy()
{

}

MenuScene::~MenuScene()
{
	
}