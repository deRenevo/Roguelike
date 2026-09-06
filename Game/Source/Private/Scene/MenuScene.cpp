// Copyright deRenevo. All rights reserved.

#include "raylib.h"

#include "Scene/MenuScene.h"
#include "Core/Scene/SceneManager.h"
#include "HUD/MenuHUD.h"
#include "Core/Actor/PlayerStart.h"
#include "Core/Math/Vector2D.h"

#include <vector>
#include <memory>

void MenuScene::SceneConstruction()
{
	SetGameMode(std::make_unique<OTestGameMode>([this](void)
	{
		return new ATestPawn();
	}));
	APlayerStart* PlayerStart = new APlayerStart(Vector2(960, 540));
	AddActorToScene(std::unique_ptr<APlayerStart>(PlayerStart));

	Scene::SceneConstruction();
	SceneManager::GetInstance().AddToViewport(std::move(std::unique_ptr<MenuHUD>(new MenuHUD())));

	for (int i = -20; i < 100; ++i)
	{
		ATestActor* TestActor = new ATestActor();
		if (i % 2 == 0)
		{
			TestActor->Col = LIME;
		}
		TestActor->SetLocation(Vector2(i * 50, 1000));

		AddActorToScene(std::unique_ptr<AActor>(TestActor));
	}
	
	FVector2D Vector2D = FVector2D::ZeroVector;
	FVector2D vec = Vector2D.Normalized();
	printf("Vector2D = %f, %f\n", vec.X, Vector2D.Y);
}

void MenuScene::Tick(float DeltaTick)
{
	Scene::Tick(DeltaTick);
}

void MenuScene::Destroy()
{

}

MenuScene::~MenuScene()
{

}
