// Copyright deRenevo. All rights reserved.

#pragma once

#include <Core/Actor/Actor.h>

class APawn;
class InputManager;

class APlayerController : public AActor
{
    APawn* PlayerPawn = nullptr;
protected:
    virtual void SetupPlayerInputComponent(InputManager& inputManager);

public:
    APlayerController();
    APlayerController(Vector2 worldLocation);
    APlayerController(Vector2 worldLocation, std::string name);

    virtual void BeginPlay();

    void Possess(APawn* pawn);
    void UnPossess();
};