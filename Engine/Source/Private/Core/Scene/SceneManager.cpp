// Copyright deRenevo. All rights reserved.


#include "Core/Scene/SceneManager.h"
#include <algorithm>
#include <iostream>

#include "Core/Manager/CollisionManager.h"
#include "Core/Manager/InputManager.h"
#include "Core/Manager/TextureManager.h"

void SceneManager::LoadScene(std::unique_ptr<OScene> scene)
{
	std::cout << "LoadScene | LoadScene START, scene = " << scene.get() << "\n";

	if (CorrectScene)
	{
		std::cout << "LoadScene | Exiting old scene\n";
		CorrectScene->OnExit();
	}

	if (!HUDViewport.empty())
	{
		HUDViewport.clear();
	}

	TextureManager::GetInstance().ClearTextureMap();
	CollisionManager::GetInstance().ClearCollisionComponents();
	InputManager::GetInstance().ClearSubscribedKeys();

	CorrectScene = std::move(scene);
	std::cout << "LoadScene | Scene moved, CorrectScene = " << CorrectScene.get() << "\n";

	if (CorrectScene)
	{
		std::cout << "LoadScene | Entering new scene\n";
		CorrectScene->OnEnter();
		std::cout << "LoadScene | Scene entered\n";
	}

	std::cout << "LoadScene | LoadScene END\n";
}

void SceneManager::AddToViewport(std::unique_ptr<HUD> hud)
{
	if (!hud) return;
	hud->OnEnter();
	HUDViewport.push_back(std::move(hud));
}

void SceneManager::RemoveHUD(HUD* hud)
{
	if (!hud) return;

	auto ptr = std::ranges::find_if(HUDViewport,
		[hud](const std::unique_ptr<HUD>& it)
		{
			return it.get() == hud;
		});

	if (ptr != HUDViewport.end())
	{
		(*ptr)->OnExit();
		HUDViewport.erase(ptr);
	}
}

void SceneManager::Tick(float DeltaTime)
{
	if (CorrectScene)
	{
		CorrectScene->DoTick(DeltaTime);
	}

	for (auto& hud : HUDViewport)
	{
		if (!hud) continue;;
		hud->DoTick(DeltaTime);
	};
}

void SceneManager::Draw()
{
	if (CorrectScene)
	{
		CorrectScene->DoDraw();
	}

	for (auto& hud : HUDViewport)
	{
		if (!hud) continue;;
		hud->DoDraw();
	};
}

OScene* SceneManager::GetScene()
{
	return CorrectScene.get();
}

void SceneManager::Shutdown()
{
	if (CorrectScene)
	{
		CorrectScene->OnExit();
		CorrectScene.reset();
	}
}

//=>getter and setter

SceneManager& SceneManager::GetInstance()
{
	static SceneManager SM;
	return SM;
}
