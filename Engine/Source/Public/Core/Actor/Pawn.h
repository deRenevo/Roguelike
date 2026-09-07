// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Actor/Actor.h"
#include "Core/Actor/PlayerController.h"

#include <memory>

class APawn : public AActor
{
	APlayerController* OwnerPlayerController = nullptr;

protected:
	virtual void Tick(float DeltaTime) override;

public:
	APawn();
	APawn(FVector2D worldLocation);
	APawn(FVector2D worldLocation, const std::string& name);
	virtual void SetupPlayerInputComponent(InputManager& inputManager);

	virtual void BeginPlay() override;

	void PossessedBy(APlayerController* playerController);
	void UnPossessed();
};
