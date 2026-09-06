// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Actor/Actor.h"
#include "Core/Actor/PlayerController.h"
#include "Core/Object/CameraComponent.h"

#include <memory>

class APawn : public AActor
{
	std::unique_ptr<OCameraComponent> RootCameraComponent;
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

	//setters
	void SetRootCameraComponent(std::unique_ptr<OCameraComponent> rootCameraComponent);

	//getters
	bool HasRootCameraComponent() const
	{
		return RootCameraComponent != nullptr;
	}

	OCameraComponent* GetRootCameraComponent() const
	{
		return RootCameraComponent.get();
	}
};
