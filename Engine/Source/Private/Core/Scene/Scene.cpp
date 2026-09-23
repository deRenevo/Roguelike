// Copyright deRenevo. All rights reserved.

#include "Core/Scene/Scene.h"

#include <iostream>
#include <algorithm>
#include <memory>

#include "Core/Manager/CollisionManager.h"
#include "Core/Manager/InputManager.h"

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

void OScene::DoTick(float DeltaTime)
{
	if (GetIsPendingKill())
		return; // if starting process deleting object thet stop Function 
	Tick(DeltaTime);
}

void OScene::DoDraw()
{
	if (GetIsPendingKill())
		return; // if starting process deleting object thet stop Function 

	if (RootCameraComponent)
	{
		BeginMode2D(RootCameraComponent->GetCamera());
		Draw(RootCameraComponent->GetViewBox());
		EndMode2D();
	}
	else
	{
		Draw({
			{0.f, 0.f},
			{1000000.f, 1000000.f}
		});
	}
}


void OScene::Tick(float DeltaTime)
{
	for (std::unique_ptr<AActor>& Actor : ActorsOnScene)
	{
		Actor->DoTick(DeltaTime);
	}

	CollisionManager::GetInstance().Tick(DeltaTime);
}

void OScene::Draw(const FBox2D& cameraViewportBounds)
{
	for (std::unique_ptr<AActor>& Actor : ActorsOnScene)
	{
		Actor->DoDraw(cameraViewportBounds);
	}
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
