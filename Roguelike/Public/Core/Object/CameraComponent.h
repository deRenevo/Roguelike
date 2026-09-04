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

	void Tick(float DeltaTime);

	//setters
	void SetCamera(const Camera2D& camera)
	{
		Camera = camera;
	}

	void SetOwner(AActor* owner)
	{
		Owner = owner;
	}

	//getters
	Vector2 GetCameraLocation() const
	{
		if (!Owner)
		{
			return {0, 0};
		}

		return Owner->GetLocation();
	}

	Camera2D GetCamera() const
	{
		return Camera;
	}

};
