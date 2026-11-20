// Copyright deRenevo. All rights reserved.

#include "Core/Component/CollisionComponent.h"

#include "Core/Manager/CollisionManager.h"

OCollisionComponent::~OCollisionComponent()
{
	CollisionManager::GetInstance().RemoveCollisionComponent(this);
}

void OCollisionComponent::Tick(const float deltaTime)
{
	OSceneComponent::Tick(deltaTime);

	if (bIsColliding)
	{
		OnCollisionDelegate.Broadcast();
	}

	if (bIsCollidingOldFrame && !bIsColliding)
	{
		OnEndCollisionDelegate.Broadcast();
	}

	if (!bIsCollidingOldFrame && bIsColliding)
	{
		OnStartCollisionDelegate.Broadcast();
	}

	bIsCollidingOldFrame = bIsColliding;
	bIsColliding = false;
}

void OCollisionComponent::OnAttach()
{
	OSceneComponent::OnAttach();

	CollisionManager::GetInstance().AddCollisionComponent(this);
}

void OCollisionComponent::OnDetach()
{
	OSceneComponent::OnDetach();
}
