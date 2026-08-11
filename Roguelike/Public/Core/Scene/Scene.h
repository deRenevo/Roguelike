// Copyright deRenevo. All rights reserved.

#pragma once

#include <Core/Object/Object.h>
#include <Core/Actor/Actor.h>
#include <vector>
#include <memory>

class Scene : public OObject
{
	std::vector<std::unique_ptr<AActor>> ActorsOnScene;

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
	void AddActorToScene(std::unique_ptr<AActor>  actor);
	std::vector<AActor*> GetActorsOnScene() const;
	void RemoveActorOnScene(AActor* actor);
	
};