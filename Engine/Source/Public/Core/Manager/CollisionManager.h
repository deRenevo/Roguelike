// Copyright deRenevo. All rights reserved.

#pragma once

#include <vector>

#include "Core/Component/CollisionComponent.h"

class OCollisionComponent;

class CollisionManager
{
	std::vector<OCollisionComponent*> CollisionComponents;

public:
	virtual ~CollisionManager() = default;
	virtual void Tick(float deltaTime);

	void AddCollisionComponent(OCollisionComponent* collisionComponent)
	{
		const uint32 Size = static_cast<uint32>(CollisionComponents.size()); 
		if (Size == UINT32_MAX)
		{
			printf("[ERROR]Size is overflow in collision component list\n");
			return;
		}
		
		collisionComponent->SetRegistryIndex(Size);
		CollisionComponents.push_back(collisionComponent);
	}

	void RemoveCollisionComponent(OCollisionComponent* collisionComponent)
	{
		if (collisionComponent->GetRegistryIndex() == UINT32_MAX)
		{
			printf("[CRITICAL ERROR] Collision nor remove because component not authorized\n");
			return;
		}
		
		if (const uint32 Last = CollisionComponents.size() - 1; collisionComponent->GetRegistryIndex() != Last)
		{
			CollisionComponents[collisionComponent->GetRegistryIndex()] = CollisionComponents[Last];
			CollisionComponents[collisionComponent->GetRegistryIndex()]->SetRegistryIndex(collisionComponent->GetRegistryIndex());
		}
		CollisionComponents.pop_back();
		collisionComponent->SetRegistryIndex(UINT32_MAX);
	}
	
	void ClearCollisionComponents()
	{
		CollisionComponents.clear();
	}

	//getters
	static CollisionManager& GetInstance()
	{
		static CollisionManager CM;
		return CM;
	}
};
