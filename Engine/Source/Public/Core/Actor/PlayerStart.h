// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Actor/Actor.h"

class APlayerStart : public AActor
{
public:
	APlayerStart();
	APlayerStart(FVector2D worldLocation, std::string name);
	APlayerStart(FVector2D worldLocation);

	virtual void BeginPlay() override;
};
