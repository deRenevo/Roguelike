// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Actor/Actor.h"

class APlayerStart : public AActor
{
	FVector2D WorldLocation;

public:
	APlayerStart();
	APlayerStart(FVector2D worldLocation, const std::string& name);
	explicit APlayerStart(FVector2D worldLocation);

	virtual void BeginPlay() override;
};
