// Copyright deRenevo. All rights reserved.


#include "Core/Actor/PlayerController.h"
#include "Core/Input/InputManager.h"
#include "Core/Actor/Pawn.h"

#include <memory>

void APlayerController::SetupPlayerInputComponent(InputManager& inputManager)
{

}

APlayerController::APlayerController() : AActor()
{

}

APlayerController::APlayerController(Vector2 worldLocation) : AActor(worldLocation)
{

}

APlayerController::APlayerController(Vector2 worldLocation, std::string name) : AActor(worldLocation, name)
{

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
