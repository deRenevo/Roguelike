// Copyright deRenevo. All rights reserved.

#pragma once

#include <Core/Scene/Scene.h>
#include <Core/Actor/Actor.h>
#include <Core/Input/InputManager.h>
#include <Core/Actor/Pawn.h>
#include <vector>
#include <iostream>

class MenuHUD;
class WButton;
//====== Test code
class ATestPawn : public APawn
{
	virtual void Draw() override
	{
		DrawRectangle(GetActorLocation().x - 50 / 2, GetActorLocation().y - 50 / 2, 50, 50, RED);
	};

	virtual void SetupPlayerInputComponent(InputManager& inputManager) override
	{
		inputManager.SubscribeKey(KeyboardKey::KEY_A, EInputType::Held, [this](void){this->Move({-1,0});});
		inputManager.SubscribeKey(KeyboardKey::KEY_D, EInputType::Held, [this](void){this->Move({1,0});});
		inputManager.SubscribeKey(KeyboardKey::KEY_W, EInputType::Held, [this](void){this->Move({0,-1});});
		inputManager.SubscribeKey(KeyboardKey::KEY_S, EInputType::Held, [this](void){this->Move({0,1});});
	};

	Vector2 InputMove = {0,0};
	int MoveSpeed = 20;

	virtual void Tick(float DeltaTime) override
	{
		Vector2 Location = GetActorLocation();
		SetActorLocation({Location.x + InputMove.x * MoveSpeed, Location.y + InputMove.y * MoveSpeed});
		InputMove = {0,0};
		APawn::Tick(DeltaTime);
	};

public:
	void Move(Vector2 deltaMove)
	{
		InputMove = {InputMove.x + deltaMove.x, InputMove.y + deltaMove.y};
	}
};

class ATestActor : public AActor
{
	virtual void Draw() override
	{
		DrawRectangle(GetActorLocation().x, GetActorLocation().y, 50, 50, Col);
	};

public:
	Color Col = RAYWHITE;
};
// ==========================
class MenuScene : public Scene
{

public:
	virtual ~MenuScene() override;

private:
	MenuHUD* MenuHud;
	ATestActor* TestActor;

protected:
	virtual void SceneConstruction() override;
	virtual void Tick(float DeltaTick) override;
	virtual void Destroy() override;
};

