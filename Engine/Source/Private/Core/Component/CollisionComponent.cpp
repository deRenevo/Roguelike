// Copyright deRenevo. All rights reserved.

#include "Core/Component/CollisionComponent.h"

#include "Core/Manager/CollisionManager.h"
#include "Core/Manager/DebugManager.h"

void OCollisionComponent::Tick(float deltaTime)
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

void OCollisionComponent::Draw()
{
	OSceneComponent::Draw();

	if (ODebugManager::bIsVisibleCollision)
	{
		if (bIsColliding)
		{
			DrawRectangleLines(GetWorldLocation().X + GetAlignment().X, GetWorldLocation().Y + GetAlignment().Y, GetSize().X, GetSize().Y, RED); //test
		}
		else
		{
			DrawRectangleLines(GetWorldLocation().X + GetAlignment().X, GetWorldLocation().Y + GetAlignment().Y, GetSize().X, GetSize().Y, LIME); //test
		}
	}
}

void OCollisionComponent::OnAttach()
{
	OSceneComponent::OnAttach();

	OCollisionManager::GetInstance().AddCollisionComponent(this);
}

void OCollisionComponent::OnDetach()
{
	OSceneComponent::OnDetach();

	OCollisionManager::GetInstance().RemoveCollisionComponent(this);
}
