// Copyright deRenevo. All rights reserved.

#include "Core/Object/GameMode.h"

#include "Core/Scene/SceneManager.h"
#include "Core/Scene/Scene.h"
#include "Core/Actor/Pawn.h"
#include "Core/Actor/PlayerController.h"
#include "Core/Actor/PlayerStart.h"

#include <memory>

OGameMode::OGameMode(std::function<APlayerController*()> controllerClass) : ControllerClass(controllerClass)
{
}

OGameMode::OGameMode(std::function<APlayerController *()> controllerClass, std::function<APawn*()> pawnClass)
	: ControllerClass(controllerClass), PawnClass(pawnClass)
{
}

void OGameMode::BeginPlay()
{
	AddNewPlayer();
}

void OGameMode::EndPlay()
{

}

void OGameMode::RestartPlayer()
{

}

void OGameMode::AddNewPlayer()
{
	std::unique_ptr<APlayerController> PC(ControllerClass());

	if (!PC)
	{
		return;
	}

	APlayerStart* PlayerStart = SceneManager::GetInstance().GetScene()->GetPlayerStart();
	Vector2 StartPointLocation;
	if (PlayerStart)
	{
		StartPointLocation = PlayerStart->GetLocation();
	}
	else
	{
		StartPointLocation = {0, 0};
	}

	PC->SetLocation(StartPointLocation);
	APlayerController* RawPC = PC.get();
	SceneManager::GetInstance().GetScene()->AddActorToScene(std::move(PC));

	if (PawnClass)
	{
		std::unique_ptr<APawn> Pawn(PawnClass());

		if (!Pawn)
		{
			return;
		}

		Pawn->SetLocation(StartPointLocation);
		RawPC->Possess(Pawn.get());
		SceneManager::GetInstance().GetScene()->AddActorToScene(std::move(Pawn));
	}
}
