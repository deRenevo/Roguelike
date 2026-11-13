// Copyright deRenevo. All rights reserved.

#include "Core/Scene/Scene.h"

#include "Core/Manager/CollisionManager.h"
#include "Core/Manager/InputManager.h"
#include "Core/Actor/Actor.h"
#include "Core/Game/GameMode.h"
#include "Core/Manager/RenderManager.h"

#include <algorithm>
#include <memory>

OScene::~OScene()
{

}

void OScene::OnEnter()
{
	PreSceneConstruction();
	SceneConstruction();
	PostSceneConstruction();

	if (GameMode)
	{
		GameMode->BeginPlay();
	}
}

void OScene::OnExit()
{
	SetIsPendingKill();
}

void OScene::DoTick(float deltaTime)
{
	if (GetIsPendingKill())
		return; // if starting process deleting object thet stop Function 
	Tick(deltaTime);
}

void OScene::DoDraw()
{
	if (GetIsPendingKill())
		return; // if starting process deleting object thet stop Function 

	if (RootCameraComponent)
	{
		BeginMode2D(RootCameraComponent->GetCamera());
		RenderManager::GetInstance().Render(RootCameraComponent->GetViewBox());
		EndMode2D();
	}
	else
	{
		RenderManager::GetInstance().Render(RootCameraComponent->GetViewBox());
	}
}

void OScene::Tick(float deltaTime)
{
	for (std::unique_ptr<AActor>& Actor : ActorsOnScene)
	{
		Actor->DoTick(deltaTime);
	}

	CollisionManager::GetInstance().Tick(deltaTime);
}

void OScene::SceneConstruction()
{

}

void OScene::PreSceneConstruction()
{

}

void OScene::PostSceneConstruction()
{

}

std::vector<AActor*> OScene::GetActorsOnScene() const
{
	std::vector<AActor*> Actors;
	for (const std::unique_ptr<AActor>& Actor : ActorsOnScene)
	{
		if (Actor && !Actor->GetIsPendingKill())
		{
			Actors.push_back(Actor.get());
		}
	}

	return Actors;
}

void OScene::RemoveActorOnScene(AActor* actor)
{
	if (!actor)
		return;

	auto It = std::ranges::find_if(ActorsOnScene,
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

void OScene::AddActorToScene(std::unique_ptr<AActor> actor)
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
