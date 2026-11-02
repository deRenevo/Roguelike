// Copyright deRenevo. All rights reserved.

#include  "Block/Floor.h"

#include "Core/Component/RenderSpriteComponent.h"

AFloor::AFloor(const std::string& name) : AActor(name)
{
	std::unique_ptr<ORenderSpriteComponent> SpriteComponent = std::make_unique<ORenderSpriteComponent>(static_cast<uint8>(64));
	FloorRenderSpriteComponent = SpriteComponent.get();
	GetRootSceneComponent()->AddChild(std::move(SpriteComponent));
}

AFloor::AFloor() : AFloor("Floor")
{

}
