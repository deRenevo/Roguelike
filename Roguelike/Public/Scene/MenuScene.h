// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Scene/Scene.h"
#include "Core/Actor/Actor.h"
#include "Core/Object/GameMode.h"
#include "Core/Input/InputManager.h"
#include "Core/Actor/Pawn.h"
#include "Roguelike.h"
#include "Core/Component/OSpriteComponent.h"

class MenuHUD;
class WButton;

//====== Test code
class ATestPawn : public APawn
{
	virtual void SetupPlayerInputComponent(InputManager& inputManager) override
	{
		inputManager.SubscribeKey(KeyboardKey::KEY_ESCAPE, EInputType::Pressed, [](void)
		{
			Roguelike::GetInstance().Stop();
		});
		inputManager.SubscribeKey(KeyboardKey::KEY_A, EInputType::Held, [this](void)
		{
			this->Move({-1, 0});
		});
		inputManager.SubscribeKey(KeyboardKey::KEY_D, EInputType::Held, [this](void)
		{
			this->Move({1, 0});
		});
		inputManager.SubscribeKey(KeyboardKey::KEY_W, EInputType::Held, [this](void)
		{
			this->Move({0, -1});
		});
		inputManager.SubscribeKey(KeyboardKey::KEY_S, EInputType::Held, [this](void)
		{
			this->Move({0, 1});
		});
		inputManager.SubscribeKey(KeyboardKey::KEY_LEFT_SHIFT, EInputType::Pressed, [this](void)
		{
			this->SetFastMove(true);
		});
		inputManager.SubscribeKey(KeyboardKey::KEY_LEFT_SHIFT, EInputType::Released, [this](void)
		{
			this->SetFastMove(false);
		});
	};

	Vector2 InputMove = {0, 0};
	int MoveSpeed = 100;
	int FastMoveSpeed = 400;
	bool bIsFastMove = false;

	virtual void Tick(float DeltaTime) override
	{
		Vector2 Location = GetLocation();
		SetLocation({Location.x + InputMove.x * (bIsFastMove ? FastMoveSpeed : MoveSpeed) * DeltaTime,
					Location.y + InputMove.y * (bIsFastMove ? FastMoveSpeed : MoveSpeed) * DeltaTime});

		InputMove = {0, 0};
		APawn::Tick(DeltaTime);
	};

public:
	ATestPawn()
	{
		OSpriteComponent* SpriteComponent = new OSpriteComponent();
		SpriteComponent->LoadTexture("Assets/block.png");
		SpriteComponent->SetSpriteAlignment(Vector2(-32,-32));
		GetRootSceneComponent()->AddChild(std::unique_ptr<OSpriteComponent>(SpriteComponent));
	}

public:
	void Move(Vector2 deltaMove)
	{
		InputMove = {InputMove.x + deltaMove.x, InputMove.y + deltaMove.y};
	};

	void SetFastMove(bool isFastMove)
	{
		bIsFastMove = isFastMove;
	};
};

class ATestActor : public AActor
{
	virtual void Draw() override
	{
		DrawRectangle(GetLocation().x, GetLocation().y, 50, 50, Col);
	};

public:
	Color Col = RAYWHITE;
};

class OTestGameMode : public OGameMode
{

public:
	OTestGameMode(std::function<APawn*()> pawnClass) : OGameMode([](void){return new APlayerController();}, pawnClass)
	{

	};
};

// ==========================

class MenuScene : public Scene
{

public:
	virtual ~MenuScene() override;

private:

protected:
	virtual void SceneConstruction() override;
	virtual void Tick(float DeltaTick) override;
	virtual void Destroy() override;
};
