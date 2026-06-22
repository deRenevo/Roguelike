#include <Core/Scene/SceneManager.h>

void SceneManager::LoadScene(std::unique_ptr<Scene> scene)
{
	if (!scene)
	{
		std::cout << "SceneManager::LoadScene | scene is not valid";
		return;
	}

	if (CorrectScene)
	{
		CorrectScene->OnExit();
	}

	CorrectScene = std::move(scene);

	if (CorrectScene)
	{
		CorrectScene->OnEnter();
	}
}

void SceneManager::LoadHUD(std::unique_ptr<HUD> hud)
{
	if (!hud)
	{
		std::cout << "SceneManager::LoadHUD | hud is not valid";
		return;
	}

	if (CorrectHUD)
	{
		CorrectHUD->OnExit();
	}

	CorrectHUD = std::move(hud);

	if (CorrectHUD)
	{
		CorrectHUD->OnEnter();
	}
}

void SceneManager::Tick(float DeltaTime)
{
	if (CorrectScene)
	{
		CorrectScene->Tick(DeltaTime);
	}

	if (CorrectHUD)
	{
		CorrectHUD->Tick(DeltaTime);
	}
}

void SceneManager::KeyPressEvent(int key)
{
	if (CorrectScene)
	{
		CorrectScene->KeyPressEvent(key);
	}

	if (CorrectHUD)
	{
		CorrectHUD->KeyPressEvent(key);
	}
}

void SceneManager::Draw()
{
	if (CorrectScene)
	{
		CorrectScene->Draw();
	}

	if (CorrectHUD)
	{
		CorrectHUD->Draw();
	}
}



//=>getter and setter

SceneManager& SceneManager::GetInstance()
{
	static SceneManager SM;
	return SM;
}