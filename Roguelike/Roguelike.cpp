#include"raylib.h"

#include <Roguelike.h>
#include <Core/Scene/SceneManager.h>
#include <Core/Scene/SceneFactory.h>
#include <Core/HUD/HUDFactory.h>

#include <iostream>

void Roguelike::Ini()
{
    const int monitor = GetCurrentMonitor();
    const int screenWidth = GetMonitorWidth(monitor);
    const int screenHeight = GetMonitorHeight(monitor);

    SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Roguelike");
    SetTargetFPS(60); //-> take it later from the settings
    SetExitKey(0);

    SceneManager::GetInstance().LoadScene(
        SceneFactory::CreateScene(SceneFactory::ESceneList::Menu)
    );

    SceneManager::GetInstance().AddToViewport(
        HUDFactory::CreateHUD(HUDFactory::EHUDList::Debug)
    );

    bIsRunning = true;
    Run();
}

void Roguelike::Stop()
{
    bIsRunning = false;
}

void Roguelike::Run()
{

    while (bIsRunning && !WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        int keyPressed = GetKeyPressed();
        
        SceneManager::GetInstance().Tick(deltaTime);
        SceneManager::GetInstance().KeyPressEvent(keyPressed);

        BeginDrawing();
        ClearBackground(BLACK);
        SceneManager::GetInstance().Draw();
        EndDrawing();
    }

    //SceneManager::GetInstance().LoadScene(nullptr);
    CloseWindow();
}

Roguelike& Roguelike::GetInstance()
{
    static Roguelike roguelike;
    return roguelike;
}
