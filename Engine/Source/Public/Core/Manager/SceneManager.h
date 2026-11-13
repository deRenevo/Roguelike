// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Scene/Scene.h"
#include "Core/HUD/HUD.h"

#include <memory>

class SceneManager
{
	std::unique_ptr<OScene> CorrectScene;
	std::vector<std::unique_ptr<HUD>> HUDViewport;

	SceneManager() = default;
	~SceneManager() = default;

public:
	virtual void LoadScene(std::unique_ptr<OScene> scene);
	virtual void AddToViewport(std::unique_ptr<HUD> hud);
	virtual void RemoveHUD(HUD* hud);
	virtual void Tick(float deltaTime); //-> every frame is processed
	virtual void Draw();
	void Shutdown();

	//getters
	static SceneManager& GetInstance();
	virtual OScene* GetScene();
};
