// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Scene/Scene.h"
#include "Core/Actor/Actor.h"
#include "Core/Game/GameMode.h"
#include "Core/Input/InputManager.h"
#include "Core/Actor/Pawn.h"
#include "Core/Application/Engine.h"
#include "Core/Component/CollisionComponent.h"

#include "Core/Component/SpriteComponent.h"
#include "Core/Math/CollisionMath.h"
#include "Core/Scene/SceneManager.h"

class MenuHUD;
class WButton;

//====== Test code
class ATestPawn : public APawn
{
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
	OSpriteComponent* SpriteComponent = nullptr;
	ATestPawn()
	{
		SpriteComponent = new OSpriteComponent();
		SpriteComponent->LoadTexture("Assets/block.png");
		SpriteComponent->SetSpriteAlignment(Vector2(-32, -32));
		//SpriteComponent->SetIsVisible(false);
		GetRootSceneComponent()->AddChild(std::unique_ptr<OSpriteComponent>(SpriteComponent));

		OCameraComponent* CameraComponent = new OCameraComponent();
		SceneManager::GetInstance().GetScene()->SetRootCameraComponent(CameraComponent);
		GetRootSceneComponent()->AddChild(std::unique_ptr<OCameraComponent>(CameraComponent));

		OCollisionComponent* CollisionComponent = new OCollisionComponent();
		CollisionComponent->SetSize({60, 60});
		CollisionComponent->SetAlignment({-30, -30});
		
		CollisionComponent->OnStartCollisionDelegate.Add(std::bind(&ATestPawn::OnCollisionStart, this));
		CollisionComponent->OnEndCollisionDelegate.Add(std::bind(&ATestPawn::OnCollisionEnd, this));
		
		GetRootSceneComponent()->AddChild(std::unique_ptr<OCollisionComponent>(CollisionComponent));
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
};

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
};

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
