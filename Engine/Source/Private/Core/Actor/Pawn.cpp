// Copyright deRenevo. All rights reserved.

#include "Core/Actor/Pawn.h"

void APawn::SetupPlayerInputComponent(InputManager& inputManager)
{
	//Test function. Processing input used global input system for Test input system.
	//Next rework system (Player controller for input control)
	//Test system using Instance class Input manager 
}

void APawn::Tick(float DeltaTime)
{
	
}

APawn::APawn() : AActor()
{

}

APawn::APawn(FVector2D worldLocation) : AActor(worldLocation)
{

}

APawn::APawn(FVector2D worldLocation, const std::string& name) : AActor(worldLocation, name)
{

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