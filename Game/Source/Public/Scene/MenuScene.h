// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Scene/Scene.h"
#include "Core/Actor/Actor.h"
#include "Core/Game/GameMode.h"
#include "Core/Manager/InputManager.h"
#include "Core/Actor/Pawn.h"
#include "Core/Application/Engine.h"
#include "Core/Component/CollisionComponent.h"

#include "Core/Component/SpriteComponent.h"
#include "Core/Component/StaticSpriteComponent.h"
#include "Core/Math/CollisionMath.h"
#include "Core/Manager/SceneManager.h"

class MenuHUD;
class WButton;

//====== Test code
class ATestPawn : public APawn
{
	FMulticastDelegateHandle Handle;

	virtual void SetupPlayerInputComponent(InputManager& inputManager) override
	{
		inputManager.SubscribeKey(KeyboardKey::KEY_ESCAPE, EInputType::Pressed, [](void)
		{
			OEngine::GetInstance().Stop();
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
		inputManager.SubscribeKey(KeyboardKey::KEY_F, EInputType::Pressed, [this](void)
		{
			this->OffLoadScene();
		});
		Handle = inputManager.SubscribeKey(KeyboardKey::KEY_R, EInputType::Pressed, [this](void)
		{
			this->LoadScene();
		});
	}

	Vector2 InputMove = {0, 0};
	int MoveSpeed = 100;
	int FastMoveSpeed = 400;
	bool bIsFastMove = false;

	virtual void Tick(float DeltaTime) override
	{
		APawn::Tick(DeltaTime);
		Vector2 Location = GetLocation();
		SetLocation({Location.x + InputMove.x * (bIsFastMove ? FastMoveSpeed : MoveSpeed) * DeltaTime,
					Location.y + InputMove.y * (bIsFastMove ? FastMoveSpeed : MoveSpeed) * DeltaTime});

		InputMove = {0, 0};
	}

public:
	OStaticSpriteComponent* StaticSpriteComponent = nullptr;

	ATestPawn()
	{
		StaticSpriteComponent = new OStaticSpriteComponent();
		StaticSpriteComponent->UpdateSprite("Assets/block.png");
		StaticSpriteComponent->GetCollisionComponent()->SetStatic(false);
		StaticSpriteComponent->SetAlignment({-static_cast<float>(StaticSpriteComponent->GetSpriteComponent()->GetTexture()->width / 2),
											-static_cast<float>(StaticSpriteComponent->GetSpriteComponent()->GetTexture()->height / 2)});
		GetRootSceneComponent()->AddChild(std::unique_ptr<OStaticSpriteComponent>(StaticSpriteComponent));

		OCameraComponent* CameraComponent = new OCameraComponent();
		CameraComponent->SetZoom(1.f);
		SceneManager::GetInstance().GetScene()->SetRootCameraComponent(CameraComponent);
		GetRootSceneComponent()->AddChild(std::unique_ptr<OCameraComponent>(CameraComponent));
	}

public:
	void OnCollisionStart() const
	{
		//SpriteComponent->SetIsVisible(true);
	}

	void OnCollisionEnd() const
	{
		//SpriteComponent->SetIsVisible(false);
	}

	void Move(Vector2 deltaMove)
	{
		InputMove = {InputMove.x + deltaMove.x, InputMove.y + deltaMove.y};
	}

	void SetFastMove(bool isFastMove)
	{
		bIsFastMove = isFastMove;
	}

	static void LoadScene();

	void OffLoadScene() const
	{
		InputManager::GetInstance().UnsubscribeKey(Handle);
	}
};

/*
class ATestActor : public AActor
{
public:
	ATestActor()
	{
		OCollisionComponent* CollisionComponent = new OCollisionComponent();
		CollisionComponent->SetSize({50, 50});
		CollisionComponent->SetStatic(true);
		GetRootSceneComponent()->AddChild(std::unique_ptr<OCollisionComponent>(CollisionComponent));
	}

	virtual void Draw() override
	{
		AActor::Draw();

		DrawRectangle(GetLocation().X + 5, GetLocation().Y + 5, 40, 40, Col);
	}

public:
	Color Col = RAYWHITE;
};*/

class OTestGameMode : public OGameMode
{

public:
	OTestGameMode(const std::function<APawn*()>& pawnClass) : OGameMode([](void)
	{
		return new APlayerController();
	}, pawnClass)
	{

	}
};

// ==========================

class OMenuScene : public OScene
{

public:
	virtual ~OMenuScene() override;

private:

protected:
	virtual void SceneConstruction() override;
	virtual void Tick(float DeltaTick) override;
};
