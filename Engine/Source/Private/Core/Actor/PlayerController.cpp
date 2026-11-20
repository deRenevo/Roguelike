// Copyright deRenevo. All rights reserved.

#include "Core/Actor/PlayerController.h"

#include "Core/Manager/InputManager.h"
#include "Core/Actor/Pawn.h"

APlayerController::APlayerController() : APlayerController(FVector2D::ZeroVector, "PlayerController")
{

}

APlayerController::APlayerController(const FVector2D worldLocation) : APlayerController(worldLocation, "PlayerController")
{

}

APlayerController::APlayerController(const FVector2D worldLocation, const std::string& name) : AActor(worldLocation, name)
{

}

APlayerController::~APlayerController()
{
	for (const auto& inputHandler : InputHandlers)
	{
		InputManager::GetInstance().UnsubscribeKey(inputHandler);
	}
}

void APlayerController::BeginPlay()
{
	SetupPlayerInputComponent(InputManager::GetInstance());
}

void APlayerController::Possess(APawn* pawn)
{
	PlayerPawn = pawn;
	if (!pawn)
	{
		printf("error Pawn is nullptr");
		return;
	}

	PlayerPawn->PossessedBy(this);
	PlayerPawn->SetupPlayerInputComponent(InputManager::GetInstance());
}

void APlayerController::UnPossess()
{
	if (PlayerPawn)
	{
		PlayerPawn->UnPossessed();
		PlayerPawn = nullptr;
	}
}

void APlayerController::SetupPlayerInputComponent(InputManager& inputManager)
{
	//Test function. Processing input used global input system for Test input system.
	//Next rework system (Player controller for input control)
	//Test system using Instance class Input manager 
}

void APlayerController::SubscribeKey(KeyboardKey key, EInputType inputType, const std::function<void()>& callback)
{
	InputHandlers.push_back(InputManager::GetInstance().SubscribeKey(key, inputType, callback));
}