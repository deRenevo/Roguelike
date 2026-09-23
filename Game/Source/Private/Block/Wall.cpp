// Copyright deRenevo. All rights reserved.

#include "Block/Wall.h"

#include "Core/Component/CollisionComponent.h"
#include "Core/Component/SpriteComponent.h"
#include "Core/Component/StaticSpriteComponent.h"

AWall::AWall(const std::string& name)
{
	std::unique_ptr<OStaticSpriteComponent> StaticSpriteComponent = std::make_unique<OStaticSpriteComponent>();
	WallStaticSpriteComponent = StaticSpriteComponent.get();
	GetRootSceneComponent()->AddChild(std::move(StaticSpriteComponent));
}

AWall::AWall() : AWall("Wall")
{
}
