// Copyright deRenevo. All rights reserved.

#pragma once

#include <vector>

class OCollisionComponent;

class CollisionManager
{
	std::vector<OCollisionComponent*> CollisionComponents;
public:
	virtual ~CollisionManager() = default;
	virtual void Tick(float deltaTime);
	
	void AddCollisionComponent(OCollisionComponent* collisionComponent)
	{
		CollisionComponents.push_back(collisionComponent);
	}

	void RemoveCollisionComponent(OCollisionComponent* collisionComponent)
	{
		if (!collisionComponent)
			return;

		auto It = std::ranges::find_if(CollisionComponents,
			[collisionComponent](const OCollisionComponent* ptr)
			{
				return ptr == collisionComponent;
			});

		if (It != CollisionComponents.end())
		{
			CollisionComponents.erase(It);
		}
	}
	
	void ClearCollisionComponents()
	{
		CollisionComponents.clear();
	}

	//getters and setters

	static CollisionManager& GetInstance()
	{
		static CollisionManager CM;
		return CM;
	}
};
