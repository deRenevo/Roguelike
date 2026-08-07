// Copyright deRenevo. All rights reserved.

#pragma once

#include "raylib.h"

#include <Core/Object/Object.h>

class Scene : public OObject
{
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
};