// Copyright deRenevo. All rights reserved.

#include "Core/Application/Engine.h"
#include "Core/Manager/SceneManager.h"

#include <raylib.h>

#include "Core/Manager/InputManager.h"

OEngine::OEngine() : OObject()
{
}

OEngine& OEngine::GetInstance()
{
	static OEngine Engine;
	return Engine;
}

void OEngine::Ini(std::unique_ptr<OScene> scene)
{
	const int8 Monitor = GetCurrentMonitor();
	const int32 ScreenWidth = GetMonitorWidth(Monitor);
	const int32 ScreenHeight = GetMonitorHeight(Monitor);

	SetConfigFlags(FLAG_FULLSCREEN_MODE);
	InitWindow(ScreenWidth, ScreenHeight, "Roguelike");
	SetTargetFPS(120); //then edit in settings
	SetExitKey(0);

	SceneManager::GetInstance().LoadScene(std::move(scene));
	bIsRunning = true;
	Run();
}

void OEngine::Run()
{
	while (bIsRunning && !WindowShouldClose())
	{
		float deltaTime = GetFrameTime();

		InputManager::GetInstance().UpdateKeyInput();

		SceneManager::GetInstance().Tick(deltaTime);

		BeginDrawing();
		ClearBackground(BLACK);
		SceneManager::GetInstance().Draw();
		EndDrawing();

		if (LoadThenScene)
		{
			SceneManager::GetInstance().LoadScene(std::move(LoadThenScene));
		}
	}
	SceneManager::GetInstance().Shutdown();
	CloseWindow();
}

void OEngine::Stop()
{
	bIsRunning = false;
}

void OEngine::LoadScene(std::unique_ptr<OScene> scene)
{
	LoadThenScene = std::move(scene);
}
