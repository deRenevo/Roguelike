// Copyright deRenevo. All rights reserved.

#pragma once

#include <Core/Actor/Actor.h>
#include <Core/Input/InputManager.h>
#include <Core/Object/CameraComponent.h>

#include <memory>

class APawn : public AActor
{
    virtual void SetupPlayerInputComponent(InputManager& inputManager);

    std::unique_ptr<OCameraComponent> RootCameraComponent;

protected:
    virtual void Tick(float DeltaTime) override;

public:

    APawn();
    APawn(Vector2 worldLocation);
    APawn(Vector2 worldLocation, std::string name);

    virtual void BeginPlay() override;

    void SetRootCameraComponent(std::unique_ptr<OCameraComponent> rootCameraComponent);
    OCameraComponent* GetRootCameraComponent();
    bool HasRootCameraComponent();
};