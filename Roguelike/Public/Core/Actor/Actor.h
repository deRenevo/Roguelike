// Copyright deRenevo. All rights reserved.

#pragma once

#include "raylib.h"

#include <Core/Object/Object.h>

class AActor : public OObject
{
    Vector2 ActorWorldLocation = Vector2(0,0);  

protected:
    virtual void PreInitializeComponents();
    virtual void InitializeComponent();
    virtual void PostInitializeComponents();

    virtual void Tick(float DeltaTime);
    virtual void Draw();
public:
    AActor(Vector2 worldLocation, std::string name);
    AActor();
    AActor(Vector2 worldLocation);
    virtual ~AActor() override;

    virtual void DoInitialize() final;

    virtual void BeginPlay();
    virtual void EndPlay();
    virtual void DoTick(float DeltaTime) final;
    virtual void DoDraw() final;

    void SetActorLocation(const Vector2& location);

    Vector2 GetActorLocation() const;
};