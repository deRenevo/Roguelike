#include <Core/Scene/SceneManager.h>

void SceneManager::LoadScene(std::unique_ptr<Scene> scene)
{
	std::cout << "LoadScene | LoadScene START, scene = " << scene.get() << "\n";

	if (CorrectScene)
	{
		std::cout << "LoadScene | Exiting old scene\n";
		CorrectScene->OnExit();
	}

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
/*
void SceneManager::LoadHUD(std::unique_ptr<HUD> hud)
{
	std::cout << "Load hud \n";

	if (!hud)
	{
		std::cout << "SceneManager::LoadHUD | hud is not valid \n";
		return;
	}
	
	if (CorrectHUD)
	{
		CorrectHUD->OnExit();
	}

	CorrectHUD = std::move(hud);

	if (CorrectHUD)
	{
		std::cout << "Load hud OnEnter\n";
		CorrectHUD->OnEnter();
	}
}*/

void SceneManager::AddToViewport(std::unique_ptr<HUD> hud)
{
	if (!hud) return;
	hud->OnEnter();
	auto* ptr = hud.get();
	HUDViewport.push_back(std::move(hud));
}

void SceneManager::RemoveHUD(HUD* hud)
{
	if (!hud) return;

	auto ptr = std::find_if(HUDViewport.begin(), HUDViewport.end(),
		[hud](const std::unique_ptr<HUD>& it) {
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
		CorrectScene->Tick(DeltaTime);
	}

	for (auto& hud : HUDViewport)
	{
		if (!hud) return;
		hud->DoTick(DeltaTime);
	};
}

void SceneManager::KeyPressEvent(int key)
{
	if (CorrectScene)
	{
		CorrectScene->KeyPressEvent(key);
	}

	for (auto& hud : HUDViewport)
	{
		if (!hud) return;
		hud->KeyPressEvent(key);
	};
}

void SceneManager::Draw()
{
	if (CorrectScene)
	{
		CorrectScene->Draw();
	}

	for (auto& hud : HUDViewport)
	{
		if (!hud) return;
		hud->DoDraw();
	};
}



//=>getter and setter

SceneManager& SceneManager::GetInstance()
{
	static SceneManager SM;
	return SM;
}