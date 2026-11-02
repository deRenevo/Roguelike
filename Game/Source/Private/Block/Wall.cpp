// Copyright deRenevo. All rights reserved.

#include "Block/Wall.h"

#include "Core/Component/CollisionComponent.h"
#include "Core/Component/StaticSpriteComponent.h"

AWall::AWall(uint8 layer, const std::string& name)
{
	std::unique_ptr<OStaticSpriteComponent> StaticSpriteComponent = std::make_unique<OStaticSpriteComponent>(name, layer);
	WallStaticSpriteComponent = StaticSpriteComponent.get();
	GetRootSceneComponent()->AddChild(std::move(StaticSpriteComponent));
}

AWall::AWall(uint8 layer) : AWall(layer,"Wall")
{
}
