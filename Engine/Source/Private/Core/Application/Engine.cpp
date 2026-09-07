// Copyright deRenevo. All rights reserved.

#include "Core/Application/Engine.h"
#include "Core/Scene/SceneManager.h"

#include <raylib.h>

#include "Core/Input/InputManager.h"

OEngine::OEngine() : OObject()
{
}

OEngine& OEngine::GetInstance()
{
	static OEngine Engine;
	return Engine;
}

void OEngine::Ini(std::unique_ptr<Scene> scene)
{
	const int8 Monitor = GetCurrentMonitor();
	const int32 ScreenWidth = GetMonitorWidth(Monitor);
	const int32 ScreenHeight = GetMonitorHeight(Monitor);
	
	SetConfigFlags(FLAG_FULLSCREEN_MODE);
	InitWindow(ScreenWidth, ScreenHeight, "Roguelike");
	SetTargetFPS(120);
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

		InputManager::GetInstance().Tick();

		SceneManager::GetInstance().Tick(deltaTime);

		BeginDrawing();
		ClearBackground(BLACK);
		SceneManager::GetInstance().Draw();
		EndDrawing();
	}
	CloseWindow();
}

void OEngine::Stop()
{
	bIsRunning = false;
}
