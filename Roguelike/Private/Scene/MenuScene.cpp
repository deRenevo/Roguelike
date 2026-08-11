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

	InputManager::GetInstance().SubscribeKey(KeyboardKey::KEY_ESCAPE, [](void){
		Roguelike::GetInstance().Stop();
	});

	SceneManager::GetInstance().GetScene()->AddActorToScene(std::unique_ptr<AActor>(new ATestActor()));
}

void MenuScene::Tick(float DeltaTick)
{
}
/*
void MenuScene::KeyPressEvent(int key)
{
	switch (key)
	{
	case KEY_SPACE:
		if (MenuState == EMenuState::StartMenu)
		{
			ToMainMenu();
		}
		break;

	case KEY_ESCAPE:
		Roguelike::GetInstance().Stop();
		break;
	default:
		break;
	}
}*/

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