#pragma once

#include <Core/Scene/SceneFactory.h>
#include <Core/Scene/Scene.h>
#include <Scene/MenuScene.h>

std::unique_ptr<Scene> SceneFactory::CreateScene(ESceneList SceneId)
{
	switch (SceneId)
	{
	case ESceneList::None:
		return nullptr;
	case ESceneList::Menu:
		return std::make_unique<MenuScene>();
	default:
		return nullptr;
	}
}
