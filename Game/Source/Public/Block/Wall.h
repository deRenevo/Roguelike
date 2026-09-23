// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Actor/Actor.h"

class OStaticSpriteComponent;

class AWall : public AActor
{
	OStaticSpriteComponent* WallStaticSpriteComponent = nullptr;

public:
	AWall(const std::string& name);
	AWall();
	
	OStaticSpriteComponent* GetSpriteComponent() const
	{
		return WallStaticSpriteComponent;
	}
};
