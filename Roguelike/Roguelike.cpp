#include"raylib.h"

#include <Roguelike.h>
#include <Core/Scene/SceneManager.h>
#include <Core/Scene/SceneFactory.h>
#include <Core/HUD/HUDFactory.h>

void Roguelike::Ini()
{
    const int monitor = GetCurrentMonitor();
    const int screenWidth = GetMonitorWidth(monitor);
    const int screenHeight = GetMonitorHeight(monitor);

    SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Roguelike");
    SetTargetFPS(60); //-> take it later from the settings

    SceneManager::GetInstance().LoadScene(
        SceneFactory::CreateScene(SceneFactory::ESceneList::Menu)
    );

    SceneManager::GetInstance().LoadHUD(
        HUDFactory::CreateHUD(HUDFactory::EHUDList::Debug)
    );

    bIsRunning = true;
    Run();
}

void Roguelike::Run()
{
    while (bIsRunning && !WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        SceneManager::GetInstance().Tick(deltaTime);

        BeginDrawing();
        ClearBackground(BLACK);
        SceneManager::GetInstance().Draw();
        EndDrawing();
    }
}

Roguelike::~Roguelike()
{
    CloseWindow();
}
