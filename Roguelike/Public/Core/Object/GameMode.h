// Copyright deRenevo. All rights reserved.

#pragma once

#include <Core/Object/Object.h>

#include <functional>

class APawn;
class APlayerController;

class OGameMode : public OObject
{
    std::function<APawn*()> PawnClass;
    std::function<APlayerController*()> ControllerClass;

public: 
    OGameMode(std::function<APlayerController*()> controllerClass);
    OGameMode(std::function<APlayerController*()> controllerClass, std::function<APawn*()> pawnClass);

    virtual void BeginPlay();
    virtual void EndPlay();

    virtual void RestartPlayer();
    virtual void AddNewPlayer(); 
};