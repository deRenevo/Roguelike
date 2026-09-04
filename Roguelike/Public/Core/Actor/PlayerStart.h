// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Actor/Actor.h"

class APlayerStart : public AActor
{
public:
	APlayerStart();
	APlayerStart(Vector2 worldLocation, std::string name);
	APlayerStart(Vector2 worldLocation);

	virtual void BeginPlay() override;
};
