// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Actor/Actor.h"

class InputManager;
class APlayerController;
class OInputManager;

class APawn : public AActor
{
	APlayerController* OwnerPlayerController = nullptr;

protected:
	virtual void Tick(float deltaTime) override;

public:
	APawn();
	explicit APawn(FVector2D worldLocation);
	APawn(FVector2D worldLocation, const std::string& name);
	virtual void SetupPlayerInputComponent(InputManager& inputManager);

	virtual void BeginPlay() override;

	void PossessedBy(APlayerController* playerController);
	void UnPossessed();
};
