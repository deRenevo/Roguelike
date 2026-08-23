// Copyright deRenevo. All rights reserved.


#include <Core/Actor/PlayerController.h>
#include <Core/Input/InputManager.h>

void APlayerController::SetupPlayerInputComponent(InputManager &inputManager)
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

void APlayerController::Possess(APawn *pawn)
{
    PlayerPawn = pawn;
}
