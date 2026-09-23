// Copyright deRenevo. All rights reserved.

#include  "Block/Floor.h"

#include "Core/Component/SpriteComponent.h"

AFloor::AFloor(const std::string& name) : AActor(name)
{
	std::unique_ptr<OSpriteComponent> SpriteComponent = std::make_unique<OSpriteComponent>();
	FloorSpriteComponent = SpriteComponent.get();
	GetRootSceneComponent()->AddChild(std::move(SpriteComponent));
}

AFloor::AFloor() : AFloor("Floor")
{

}
