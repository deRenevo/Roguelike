// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Actor/Actor.h"

class OStaticSpriteComponent;

class AWall : public AActor
{
	OStaticSpriteComponent* WallStaticSpriteComponent = nullptr;

public:
	AWall(uint8 layer, const std::string& name);
	AWall(uint8 layer = 64);
	
	OStaticSpriteComponent* GetSpriteComponent() const
	{
		return WallStaticSpriteComponent;
	}
};
