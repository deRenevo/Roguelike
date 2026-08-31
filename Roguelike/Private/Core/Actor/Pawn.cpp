// Copyright deRenevo. All rights reserved.

#include <Core/Actor/Pawn.h>
#include <Core/Scene/SceneManager.h>

void APawn::SetupPlayerInputComponent(InputManager& inputManager)
{
	//Test function. Procsessing input used global input system for Test input system.
	//Next rework system (Player controler for input constrol)
	//Test system using Instance class Input menager 
}

void APawn::Tick(float DeltaTime)
{
	if (RootCameraComponent)
	{
		RootCameraComponent->Tick(DeltaTime);
	}
}

APawn::APawn() : AActor()
{
	RootCameraComponent = std::make_unique<OCameraComponent>();
}

APawn::APawn(Vector2 worldLocation) : AActor(worldLocation)
{
	RootCameraComponent = std::make_unique<OCameraComponent>();
}

APawn::APawn(Vector2 worldLocation, std::string name) : AActor(worldLocation, name)
{
	RootCameraComponent = std::make_unique<OCameraComponent>();
}

void APawn::BeginPlay()
{
	AActor::BeginPlay();

	if (RootCameraComponent)
	{
		RootCameraComponent->SetOwner(this);
		SceneManager::GetInstance().GetScene()->SetRootCameraComponent(RootCameraComponent.get());
	}
}

void APawn::PossessedBy(APlayerController* playerController)
{
	OwnerPlayerController = playerController;
}

void APawn::UnPossessed()
{
	OwnerPlayerController = nullptr;
	//next this clear input action for this pawn 
}

void APawn::SetRootCameraComponent(std::unique_ptr<OCameraComponent> rootCameraComponent)
{
	RootCameraComponent = std::move(rootCameraComponent);

	if (RootCameraComponent)
	{
		RootCameraComponent->SetOwner(this);
	}

	SceneManager::GetInstance().GetScene()->SetRootCameraComponent(RootCameraComponent.get());
}

OCameraComponent* APawn::GetRootCameraComponent()
{
	return RootCameraComponent.get();
}

bool APawn::HasRootCameraComponent()
{
	return RootCameraComponent != nullptr;
}
