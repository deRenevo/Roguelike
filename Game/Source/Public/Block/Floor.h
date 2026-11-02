// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Actor/Actor.h"

class ORenderSpriteComponent;

class AFloor : public AActor
{
	ORenderSpriteComponent* FloorRenderSpriteComponent = nullptr;

public:
	AFloor(const std::string& name);
	AFloor();
	
	ORenderSpriteComponent* GetSpriteComponent() const
	{
		return FloorRenderSpriteComponent;
	}
};
