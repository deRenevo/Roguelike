// Copyright deRenevo. All rights reserved.

#pragma once

#include <Core/Scene/Scene.h>
#include <vector>

class MenuHUD;
class WButton;

class MenuScene : public Scene
{

public:
	virtual ~MenuScene() override;

private:
	MenuHUD* MenuHud;

public:
	void ToMainMenu();

protected:
	virtual void SceneConstruction() override;
	virtual void Tick(float DeltaTick) override;
	virtual void Destroy() override;
};

