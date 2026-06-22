#pragma once

class HUD
{
public:
    HUD() = default;
    virtual ~HUD() = default;

    void OnEnter(); // -> Loading resources
    virtual void OnExit(); // -> Cleaning up resources
    virtual void Tick(float DeltaTime); //-> every frame is processed
    virtual void Draw();
    virtual void KeyPressEvent(int key);

protected:
    virtual void HUDConstruction(); //-> processed when changing priced
    virtual void PreHUDConstruction(); //-> processed before SceneConstruction
    virtual void PostHUDConstruction(); //-> processed after SceneConstruction
};