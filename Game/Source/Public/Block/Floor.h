// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Actor/Actor.h"

class OSpriteComponent;

class AFloor : public AActor
{
	OSpriteComponent* FloorSpriteComponent = nullptr;

public:
	AFloor(const std::string& name);
	AFloor();
	
	OSpriteComponent* GetSpriteComponent() const
	{
		return FloorSpriteComponent;
	}
};
