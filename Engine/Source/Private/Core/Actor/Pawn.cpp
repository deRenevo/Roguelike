// Copyright deRenevo. All rights reserved.

#include "Core/Actor/Pawn.h"

#include "Core/Manager/InputManager.h"

void APawn::Tick(const float deltaTime)
{
	AActor::Tick(deltaTime);
}

APawn::APawn() : APawn(FVector2D::ZeroVector, "Pawn")
{

}

APawn::APawn(const FVector2D worldLocation) : APawn(worldLocation, "Pawn")
{

}

APawn::APawn(const FVector2D worldLocation, const std::string& name) : AActor(worldLocation, name)
{

}

APawn::~APawn()
{
	for (const auto& inputHandler : InputHandlers)
	{
		InputManager::GetInstance().UnsubscribeKey(inputHandler);
	}
	InputHandlers.clear();
}

void APawn::BeginPlay()
{
	AActor::BeginPlay();
}

void APawn::PossessedBy(APlayerController* playerController)
{
	OwnerPlayerController = playerController;
}

void APawn::UnPossessed()
{
	OwnerPlayerController = nullptr;
}

void APawn::SetupPlayerInputComponent(InputManager& inputManager)
{
	//Test function. Processing input used global input system for Test input system.
	//Next rework system (Player controller for input control)
	//Test system using Instance class Input manager 
}

void APawn::SubscribeKey(KeyboardKey key, EInputType inputType, const std::function<void()>& callback)
{
	InputHandlers.push_back(InputManager::GetInstance().SubscribeKey(key, inputType, callback));
}