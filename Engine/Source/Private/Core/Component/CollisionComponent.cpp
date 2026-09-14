// Copyright deRenevo. All rights reserved.

#include "Core/Component/CollisionComponent.h"

#include "Core/Manager/CollisionManager.h"

void OCollisionComponent::Tick(float deltaTime)
{
	OSceneComponent::Tick(deltaTime);
	
	
	//For HARD CODE
	if (bIsColliding)
	{
		for (auto& Function : OnCollisionCollBackFunctions)
		{
			Function();
		}
	}
	
	if (bIsCollidingOldFrame && !bIsColliding)
	{
		for (auto& Function : OnEndCollisionCollBackFunctions)
		{
			Function();
		}
	}
	
	if (!bIsCollidingOldFrame && bIsColliding)
	{
		for (auto& Function : OnStartCollisionCollBackFunctions)
		{
			Function();
		}
	}
	
	//============
	bIsCollidingOldFrame = bIsColliding;
	bIsColliding = false;
}

void OCollisionComponent::Draw()
{
	OSceneComponent::Draw();

	if (bIsColliding)
	{
		DrawRectangleLines(GetWorldLocation().X + GetAlignment().X, GetWorldLocation().Y + GetAlignment().Y, GetSize().X, GetSize().Y, RED); //test
	}
	else
	{
		DrawRectangleLines(GetWorldLocation().X + GetAlignment().X, GetWorldLocation().Y + GetAlignment().Y, GetSize().X, GetSize().Y, LIME); //test
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
