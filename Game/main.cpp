// Copyright deRenevo. All rights reserved.
// Input point in project

#include "Core/Application/Engine.h"

#include "Scene/MenuScene.h"

#include <iostream>
#include <memory>

using namespace std;

int main()
{
	printf("Hello Roguelike");
	
	OEngine::GetInstance().Ini(std::make_unique<MenuScene>());
	return 0;
}
