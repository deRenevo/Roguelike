// Copyright deRenevo. All rights reserved.

#include <Core/Scene/Scene.h>
#include <iostream>
#include <algorithm>
#include <memory>

void Scene::OnEnter()
{
	PreSceneConstruction();;
	SceneConstruction();
	PostSceneConstruction();

	if (GameMode)
	{
		GameMode->BeginPlay();
	}
}

void Scene::OnExit()
{
	Destroy();
}

void Scene::DoTick(float DeltaTime)
{
	if (GetIsPendingKill()) return; // if sttarting process deleting object thet stop Function 
	Tick(DeltaTime);
}

void Scene::DoDraw()
{
	if (GetIsPendingKill()) return; // if sttarting process deleting object thet stop Function 

	if (RootCameraComponent)
	{
		BeginMode2D(RootCameraComponent->GetCamera());
		Draw();
		EndMode2D();
	}
	else
	{
		Draw();
	}
}


void Scene::Tick(float DeltaTime)
{
	for (std::unique_ptr<AActor>& Actor : ActorsOnScene)
	{
		Actor->DoTick(DeltaTime);
	}
}

void Scene::Draw()
{
	for (std::unique_ptr<AActor>& Actor : ActorsOnScene)
	{
		Actor->DoDraw();
	}
}

void Scene::SceneConstruction()
{

}

void Scene::PreSceneConstruction()
{

}

void Scene::PostSceneConstruction()
{

}

void Scene::Destroy()
{
	SetIsPendingKill();
}

std::vector<AActor *> Scene::GetActorsOnScene() const
{
	std::vector<AActor *> Actors;
	for (const std::unique_ptr<AActor>& Actor : ActorsOnScene)
	{
		if (Actor && !Actor->GetIsPendingKill())
		{
			Actors.push_back(Actor.get());
		}
	}

	return Actors;
}

void Scene::RemoveActorOnScene(AActor* actor)
{
	if (!actor) return;

	auto It = std::find_if(ActorsOnScene.begin(), ActorsOnScene.end(),
							[actor](const std::unique_ptr<AActor>& ptr)
							{
								return ptr.get() == actor;
							});

	if (It != ActorsOnScene.end())
	{
		(*It)->EndPlay();
		ActorsOnScene.erase(It);
	}
}

void Scene::SetRootCameraComponent(OCameraComponent* rootCameraComponent)
{
	printf("SetCamera\n");
	RootCameraComponent = rootCameraComponent;
}

void Scene::AddActorToScene(std::unique_ptr<AActor> actor)
{
	if (!actor)
	{
		printf("Error: trying to add nullptr actor to scene\n");
		return;
	}

	actor->DoInitialize();
	actor->BeginPlay();
	ActorsOnScene.push_back(std::move(actor));
}

void Scene::SetGameMode(std::unique_ptr<OGameMode> gameMode)
{
	GameMode = std::move(gameMode);
}

void Scene::SetPlayerStart(APlayerStart* playerStart)
{
	PlayerStart = playerStart;
}

OGameMode* Scene::GetGameMode()
{
	return GameMode.get();
}

APlayerStart* Scene::GetPlayerStart()
{
	return PlayerStart;
}
