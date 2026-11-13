// Copyright deRenevo. All rights reserved.


#include "Core/Manager/SceneManager.h"

#include "Core/Manager/CollisionManager.h"
#include "Core/Manager/InputManager.h"
#include "Core/Manager/AnimationManager.h"
#include "Core/Manager/RenderManager.h"

void SceneManager::LoadScene(std::unique_ptr<OScene> scene)
{
	if (CorrectScene)
	{
		CorrectScene->OnExit();
		CorrectScene.reset();
	}

	if (!HUDViewport.empty())
	{
		HUDViewport.clear();
	}

	AnimationManager::GetInstance().ClearAnimationMap();
	RenderManager::GetInstance().ClearAll();
	TextureManager::GetInstance().ClearTextureMap();
	CollisionManager::GetInstance().ClearCollisionComponents();
	InputManager::GetInstance().ClearSubscribedKeys();

	CorrectScene = std::move(scene);

	if (CorrectScene)
	{
		CorrectScene->OnEnter();
	}
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

	const auto Ptr = std::ranges::find_if(HUDViewport,
		[hud](const std::unique_ptr<HUD>& it)
		{
			return it.get() == hud;
		});

	if (Ptr != HUDViewport.end())
	{
		(*Ptr)->OnExit();
		HUDViewport.erase(Ptr);
	}
}

void SceneManager::Tick(const float deltaTime)
{
	if (CorrectScene)
	{
		CorrectScene->DoTick(deltaTime);
	}

	for (const auto& Hud : HUDViewport)
	{
		if (!Hud) continue;;
		Hud->DoTick(deltaTime);
	};
}

void SceneManager::Draw()
{
	if (CorrectScene)
	{
		CorrectScene->DoDraw();
	}

	for (const auto& Hud : HUDViewport)
	{
		if (!Hud) continue;;
		Hud->DoDraw();
	}
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

SceneManager& SceneManager::GetInstance()
{
	static SceneManager SM;
	return SM;
}
