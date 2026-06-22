#include"raylib.h"

#include <UI/Menu.h>
#include <Roguelike.h>


Roguelike::Roguelike() : bIsRunning(false), screenWidth(0), screenHeight(0)
{
    
}

Roguelike::~Roguelike()
{
}

void Roguelike::Ini()
{
    const int monitor = GetCurrentMonitor();
    screenWidth = GetMonitorWidth(monitor);
    screenHeight = GetMonitorHeight(monitor);

    SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Roguelike");
    SetTargetFPS(60); //! next edit in menu settings
    bIsRunning = true;

    GameMenu = new Menu();

    Run();
}

void Roguelike::Run()
{
    while (bIsRunning && !WindowShouldClose())
    {
        Update();
    }

}

void Roguelike::Update()
{
    InputTick();

    BeginDrawing();
    ClearBackground(BLACK);

    GameMenu->Update();

    EndDrawing();
}

void Roguelike::Cleanup()
{
    if (bIsRunning)
    {
        CloseWindow();
        bIsRunning = false;
    }
}

void Roguelike::InputTick()
{
    int key = GetKeyPressed();

    GameMenu->InputTick(key);

    switch (key)
    {
    case KEY_ESCAPE:
        StopRunning();
        break;
    default:
        break;
    }
}

void Roguelike::StopRunning()
{
    bIsRunning = false;
}
