// Copyright deRenevo. All rights reserved.

#include "raylib.h"

#include <Core/Utility/Draw/DrawUtility.h>
#include <Core/Widgets/WidgetsElements/Button.h>
#include <Scene/MenuScene.h>
#include <Core/Scene/SceneManager.h>
#include <HUD/MenuHUD.h>
#include <Roguelike.h>
#include <Core/Input/InputManager.h>
#include <Core/Scene/SceneManager.h>


#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <functional>

void MenuScene::SceneConstruction()
{
	Scene::SceneConstruction();
	auto hud = std::make_unique<MenuHUD>();
	MenuHud = hud.get();
	SceneManager::GetInstance().AddToViewport(std::move(hud));

	InputManager::GetInstance().SubscribeKey(KeyboardKey::KEY_ESCAPE, EInputType::Pressed, [](void){
		Roguelike::GetInstance().Stop();
	});

	for (int i = -20; i < 100; ++i)
	{
		ATestActor* TestActor = new ATestActor();
		if (i % 2 == 0)
		{
			TestActor->Col = LIME;
		}
		TestActor->SetActorLocation(Vector2(i * 50, 1000));

		SceneManager::GetInstance().GetScene()->AddActorToScene(std::unique_ptr<AActor>(TestActor));
	}

	ATestPawn* TestPawn = new ATestPawn();
	TestPawn->SetActorLocation({GetScreenWidth() / 2, GetScreenHeight() / 2});

	SceneManager::GetInstance().GetScene()->AddActorToScene(std::unique_ptr<APawn>(TestPawn));
}

void MenuScene::Tick(float DeltaTick)
{
	Scene::Tick(DeltaTick);
}

void MenuScene::Destroy()
{
	if (MenuHud)
	{
		SceneManager::GetInstance().RemoveHUD(MenuHud);
	}
}

MenuScene::~MenuScene()
{
	
}