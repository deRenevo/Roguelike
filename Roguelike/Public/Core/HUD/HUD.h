#pragma once
#include <Core/Widgets/WidgetsElements/Widget.h>

#include <memory>

class HUD
{
    std::unique_ptr<Widget> RootWidget;
    bool bIsVisible = true;
    bool bIsInitialized = false;

public:
    HUD() = default;
    virtual ~HUD() = default;
    virtual void DoTick(float DeltaTime);
    virtual void DoDraw();
    void OnEnter(); // -> Loading resources
    virtual void OnExit(); // -> Cleaning up resources
    virtual void KeyPressEvent(int key);

protected:
    virtual void HUDConstruction(); //-> processed when changing priced
    virtual void PreHUDConstruction(); //-> processed before SceneConstruction
    virtual void PostHUDConstruction(); //-> processed after SceneConstruction
    virtual void Tick(float DeltaTime); //-> every frame is processed
    virtual void Draw();

    
    void SetRootWidget(Widget* rootWidget);
    void SetIsVisible(bool isVisible);

    Widget* GetRootWidget();
    bool GetIsVisible();
};