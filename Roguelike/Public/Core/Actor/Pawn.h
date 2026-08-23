// Copyright deRenevo. All rights reserved.

#pragma once

#include <Core/Actor/Actor.h>
#include <Core/Actor/PlayerController.h>
#include <Core/Input/InputManager.h>
#include <Core/Object/CameraComponent.h>

#include <memory>

class APawn : public AActor
{
    std::unique_ptr<OCameraComponent> RootCameraComponent;
    APlayerController* OwnerPlayerController = nullptr;

protected:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(InputManager& inputManager);

public:

    APawn();
    APawn(Vector2 worldLocation);
    APawn(Vector2 worldLocation, std::string name);

    virtual void BeginPlay() override;

    void SetRootCameraComponent(std::unique_ptr<OCameraComponent> rootCameraComponent);
    void SetPlayerController(APlayerController* playerController);
    OCameraComponent* GetRootCameraComponent();
    bool HasRootCameraComponent();
};