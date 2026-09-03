// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Object/Object.h"

class AActor;

class OComponent : public OObject
{
    AActor* Owner = nullptr;
    bool bIsActive = true;
    bool bIsHasBeginPlay = false;

protected:
    virtual void Tick(float DeltaTime);
    virtual void Draw(); 
public:
    
    OComponent();
    OComponent(AActor* owner);
    OComponent(const std::string& name);
    OComponent(AActor* owner, const std::string& name);

    virtual ~OComponent() override = default;

    virtual void DoTick(float DeltaTime);
    virtual void DoDraw();
    virtual void BeginPlay();
    virtual void EndPlay();
    virtual void OnAttach();
    virtual void OnDetach();


    void SetOwner(AActor* owner);
    void SetIsActive(bool isActive);

    AActor* GetOwner() const;
    bool IsActive() const;
};