// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Object/Object.h"
#include "Core/Actor/Actor.h"

#include <raylib.h>

class OCameraComponent : public OObject
{
	AActor* Owner = nullptr;
	Camera2D Camera;

public:
	OCameraComponent();
	OCameraComponent(AActor* owner);
	~OCameraComponent();

	void SetOwner(AActor* owner);
	void Tick(float DeltaTime);

	void SetCamera(const Camera2D& camera);

	Vector2 GetCameraLocation();
	Camera2D GetCamera();

};
