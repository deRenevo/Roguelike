// Copyright deRenevo. All rights reserved.

#pragma once

#include <Core/Scene/Scene.h>
#include <Core/Actor/Actor.h>
#include <Core/Input/InputManager.h>
#include <vector>

class MenuHUD;
class WButton;

class ATestActor : public AActor
{
	/*virtual void BeginPlay() override
	{
		InputManager::GetInstance().SubscribeKey(KeyboardKey::KEY_Q, [this](){
			Vector2 loc = Vector2(GetActorLocation().x - 50, GetActorLocation().y + 4);
			SetActorLocation(loc);
		});

		InputManager::GetInstance().SubscribeKey(KeyboardKey::KEY_E, [this](){
			Vector2 loc = Vector2(GetActorLocation().x + 50, GetActorLocation().y + 4);
			SetActorLocation(loc);
		});
	}*/

	virtual void Draw() override
	{
		if (GetActorLocation().y > GetScreenHeight())
		{
			Vector2 loc = Vector2(GetActorLocation().x, 0.0);
			SetActorLocation(loc);
		}

		Vector2 loc = Vector2(GetActorLocation().x, GetActorLocation().y + 4);
		SetActorLocation(loc);

		DrawRectangle(GetActorLocation().x, GetActorLocation().y, 100, 100, RED);
	};
};

class MenuScene : public Scene
{

public:
	virtual ~MenuScene() override;

private:
	MenuHUD* MenuHud;
	ATestActor* TestActor;

public:
	void ToMainMenu();

protected:
	virtual void SceneConstruction() override;
	virtual void Tick(float DeltaTick) override;
	virtual void Destroy() override;
};

