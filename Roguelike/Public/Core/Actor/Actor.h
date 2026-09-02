// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Object/Object.h"
#include "Core/Component/SceneComponent.h"

#include <raylib.h>
#include <memory>

class AActor : public OObject
{
    bool bIsHasBeginPlay = false;
    std::unique_ptr<OSceneComponent> RootSceneComponent = nullptr;
protected:
    virtual void PreInitializeComponents();
    virtual void InitializeComponent();
    virtual void PostInitializeComponents();

    virtual void Tick(float DeltaTime);
    virtual void Draw();
public:
    AActor(Vector2 worldLocation, const std::string& name);
    AActor();
    AActor(Vector2 worldLocation);
    virtual ~AActor() override;

    virtual void DoInitialize() final;

    virtual void BeginPlay();
    virtual void EndPlay();
    virtual void DoTick(float DeltaTime) final;
    virtual void DoDraw() final;

    void SetLocation(const Vector2& location) const;
    void SetRootSceneComponent(std::unique_ptr<OSceneComponent> rootSceneComponent);

    Vector2 GetLocation() const;
    OSceneComponent* GetRootSceneComponent() const;
};
