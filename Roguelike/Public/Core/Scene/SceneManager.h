#pragma once

#include <Core/Scene/Scene.h>
#include <Core/HUD/HUD.h>

#include <memory>
#include <iostream>
#include <vector>

class SceneManager
{

public:
	static SceneManager& GetInstance();

	virtual void LoadScene(std::unique_ptr<Scene> scene);
	//virtual void LoadHUD(std::unique_ptr<HUD> hud);
	virtual void AddToViewport(std::unique_ptr<HUD> hud);
	virtual void RemoveHUD(HUD* hud);
	virtual void Tick(float DeltaTime); //-> every frame is processed
	virtual void KeyPressEvent(int key);
	virtual void Draw();

private:
	SceneManager() = default;
	~SceneManager() = default;

	std::unique_ptr<Scene> CorrectScene;
	//std::unique_ptr<HUD> CorrectHUD;
	std::vector<std::unique_ptr<HUD>> HUDViewport;
};