// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Object/Object.h"

#include <functional>

class APawn;
class APlayerController;

class OGameMode : public OObject
{
	std::function<APawn*()> PawnClass;
	std::function<APlayerController*()> ControllerClass;

public:
	OGameMode() = default;
	OGameMode(const std::function<APlayerController*()>& controllerClass);
	OGameMode(const std::function<APlayerController*()>& controllerClass, const std::function<APawn*()>& pawnClass);

	virtual void BeginPlay();
	virtual void EndPlay();

	virtual void RestartPlayer();
	virtual void AddNewPlayer();
};
