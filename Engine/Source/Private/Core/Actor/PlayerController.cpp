// Copyright deRenevo. All rights reserved.


#include "Core/Actor/PlayerController.h"
#include "Core/Manager/InputManager.h"
#include "Core/Actor/Pawn.h"

#include <memory>

void APlayerController::SetupPlayerInputComponent(OInputManager& inputManager)
{

}

APlayerController::APlayerController() : AActor()
{

}

APlayerController::APlayerController(FVector2D worldLocation) : AActor(worldLocation)
{

}

APlayerController::APlayerController(FVector2D worldLocation, std::string name) : AActor(worldLocation, name)
{

}

void APlayerController::BeginPlay()
{
	SetupPlayerInputComponent(OInputManager::GetInstance());
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
	PlayerPawn->SetupPlayerInputComponent(OInputManager::GetInstance());
}

void APlayerController::UnPossess()
{
	if (PlayerPawn)
	{
		PlayerPawn->UnPossessed();
		PlayerPawn = nullptr;
	}
}
