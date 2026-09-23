// Copyright deRenevo. All rights reserved.

#include "raylib.h"

#include "Scene/MenuScene.h"
#include "Core/Manager/SceneManager.h"
#include "HUD/MenuHUD.h"
#include "Core/Actor/PlayerStart.h"
#include "Core/Math/Vector2D.h"

#include <memory>

#include "Block/Floor.h"
#include "Block/Wall.h"
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

	for (int i = 0; i < 200; ++i)
	{
		for (int j = 0; j < 200; ++j)
		{
			if (i == 0 || i == 199 || j == 0 || j == 199)
			{
				std::unique_ptr<AWall> Wall = std::make_unique<AWall>();
				Wall->GetSpriteComponent()->UpdateSprite("Assets/IndustrialTile_1.png");
				Wall->SetLocation({static_cast<float>(i * 32), static_cast<float>(j * 32)});
				Wall->SetIsTickable(false);
				AddActorToScene(std::move(Wall));
				continue;
			}


			std::unique_ptr<AFloor> Floor = std::make_unique<AFloor>();
			Floor->GetSpriteComponent()->LoadTexture("Assets/MainTestTile.png");
			Floor->SetLocation({static_cast<float>(i * 32), static_cast<float>(j * 32)});
			Floor->SetIsTickable(false);
			AddActorToScene(std::move(Floor));
		}
	}
}

void OMenuScene::Tick(float DeltaTick)
{
	OScene::Tick(DeltaTick);
}

void ATestPawn::LoadScene()
{
	OEngine::GetInstance().LoadScene(std::make_unique<OMenuScene>());
}

OMenuScene::~OMenuScene()
{

}
