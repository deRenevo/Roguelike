// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Widgets/WidgetsElements/Widget.h"

#include <memory>

class HUD
{
    std::unique_ptr<WWidget> RootWidget;
    bool bIsVisible = true;
    bool bIsInitialized = false;

public:
    HUD() = default;
    virtual ~HUD() = default;
    virtual void DoTick(float DeltaTime);
    virtual void DoDraw();
    void OnEnter(); // -> Loading resources
    virtual void OnExit(); // -> Cleaning up resources

protected:
    virtual void HUDConstruction(); //-> processed when changing priced
    virtual void PreHUDConstruction(); //-> processed before SceneConstruction
    virtual void PostHUDConstruction(); //-> processed after SceneConstruction
    virtual void Tick(float DeltaTime); //-> every frame is processed
    virtual void Draw();

    
    void SetRootWidget(std::unique_ptr<WWidget> rootWidget);
    void SetIsVisible(bool isVisible);

    WWidget* GetRootWidget();
    bool GetIsVisible();
};