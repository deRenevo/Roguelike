// Copyright deRenevo. All rights reserved.

#include "Core/Object/CameraComponent.h"

OCameraComponent::OCameraComponent() : OObject("CameraComponent")
{
	Camera.target = {0, 0};
	Camera.offset = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
	Camera.rotation = 0.0f;
	Camera.zoom = 1.0f;
}

OCameraComponent::OCameraComponent(AActor* owner) : OObject("CameraComponent")
{
	SetOwner(owner);
}

OCameraComponent::~OCameraComponent()
{
	Camera.target = {0, 0};
	Camera.offset = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
	Camera.rotation = 0.0f;
	Camera.zoom = 1.0f;
}

void OCameraComponent::Tick(float DeltaTime)
{
	if (!Owner) return;

	Vector2 ownerPos = Owner->GetLocation();
	Camera.target = ownerPos;
}
