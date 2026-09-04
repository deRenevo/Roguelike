// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Object/Object.h"
#include "Core/Actor/Actor.h"
#include "Core/Object/GameMode.h"
#include "Core/Object/CameraComponent.h"

#include <vector>
#include <memory>

class APlayerStart;

class Scene : public OObject
{
	std::vector<std::unique_ptr<AActor>> ActorsOnScene;
	OCameraComponent* RootCameraComponent;
	APlayerStart* PlayerStart;
	std::unique_ptr<OGameMode> GameMode;

public:
	Scene() = default;
	virtual ~Scene() = default;

	void OnEnter(); // -> Loading resources
	virtual void OnExit(); // -> Cleaning up resources

	virtual void DoTick(float DeltaTime) final; //-> Start point for every frame is processed
	virtual void DoDraw() final;

protected:
	virtual void Tick(float DeltaTime); //-> every frame is processed
	virtual void Draw();

	virtual void SceneConstruction(); //-> processed when changing priced
	virtual void PreSceneConstruction(); //-> processed before SceneConstruction
	virtual void PostSceneConstruction(); //-> processed after SceneConstruction
	virtual void Destroy();

public:
	void AddActorToScene(std::unique_ptr<AActor> actor);
	void RemoveActorOnScene(AActor* actor);

	//setters
	std::vector<AActor*> GetActorsOnScene() const;

	void SetRootCameraComponent(OCameraComponent* rootCameraComponent)
	{
		RootCameraComponent = rootCameraComponent;
	}

	void SetGameMode(std::unique_ptr<OGameMode> gameMode)
	{
		GameMode = std::move(gameMode);
	}

	void SetPlayerStart(APlayerStart* playerStart)
	{
		PlayerStart = playerStart;
	}

	//getters
	OGameMode* GetGameMode() const
	{
		return GameMode.get();
	}

	APlayerStart* GetPlayerStart() const
	{
		return PlayerStart;
	}
};
