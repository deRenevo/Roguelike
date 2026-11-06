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
#include "Core/Component/RenderSpriteComponent.h"
#include "HUD/DebugHUD.h"

void OMenuScene::SceneConstruction()
{
	SetGameMode(std::make_unique<OTestGameMode>([this](void)
	{
		return new ATestPawn();
	}));
	APlayerStart* PlayerStart = new APlayerStart(Vector2(960, 960));
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
				Wall->GetSpriteComponent()->UpdateSprite("Assets/IndustrialTile_" + std::to_string(GetRandomValue(1, 4)) + ".png");
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
	
	for (int i = 10; i < 15; ++i)
	{
		std::unique_ptr<AWall> Fence = std::make_unique<AWall>(128);
		Fence->GetSpriteComponent()->UpdateSprite("Assets/Fence_1.png");
		Fence->SetLocation({static_cast<float>(i * 128), static_cast<float>(980)});
		Fence->SetIsTickable(false);
		Fence->GetSpriteComponent()->SetCollisionSize(FVector2D(128, 10));
		Fence->GetSpriteComponent()->GetSpriteComponent()->SetRenderAlignment({0, -26});
		Fence->GetSpriteComponent()->GetCollisionComponent()->SetAlignment(FVector2D(0, 30));
		AddActorToScene(std::move(Fence));
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
