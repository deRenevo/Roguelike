// Copyright deRenevo. All rights reserved.

#include "raylib.h"

#include "Scene/MenuScene.h"
#include "Core/Scene/SceneManager.h"
#include "HUD/MenuHUD.h"
#include "Core/Actor/PlayerStart.h"
#include "Core/Math/Vector2D.h"

#include <memory>

#include "HUD/DebugHUD.h"

void OMenuScene::SceneConstruction()
{
	SetGameMode(std::make_unique<OTestGameMode>([this](void)
	{
		return new ATestPawn();
	}));
	APlayerStart* PlayerStart = new APlayerStart(Vector2(960, 540));
	AddActorToScene(std::unique_ptr<APlayerStart>(PlayerStart));

	OScene::SceneConstruction();
	//SceneManager::GetInstance().AddToViewport(std::move(std::make_unique<MenuHUD>()));
	SceneManager::GetInstance().AddToViewport(std::move(std::make_unique<DebugHUD>()));

	for (int i = -20; i < 100; ++i)
	{
		ATestActor* TestActor = new ATestActor();
		if (i % 2 == 0)
		{
			TestActor->Col = ORANGE;
		}
		TestActor->SetLocation(Vector2(i * 50, 1000));

		AddActorToScene(std::unique_ptr<AActor>(TestActor));
	}
}

void OMenuScene::Tick(float DeltaTick)
{
	OScene::Tick(DeltaTick);
}

void OMenuScene::Destroy()
{

}

OMenuScene::~OMenuScene()
{

}
