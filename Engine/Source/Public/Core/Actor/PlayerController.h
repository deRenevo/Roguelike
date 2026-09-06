// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Actor/Actor.h"

class APawn;
class InputManager;

class APlayerController : public AActor
{
	APawn* PlayerPawn = nullptr;

protected:
	virtual void SetupPlayerInputComponent(InputManager& inputManager);

public:
	APlayerController();
	APlayerController(FVector2D worldLocation);
	APlayerController(FVector2D worldLocation, std::string name);

	virtual void BeginPlay() override;

	void Possess(APawn* pawn);
	void UnPossess();
};
