// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Object/Object.h"

class OCollisionComponent;

class OCollisionManager : public OObject
{
	std::vector<OCollisionComponent*> CollisionComponents;

protected:
	virtual void Tick(float deltaTime);

public:
	virtual void DoTick(float deltaTime) final;
	
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

	static OCollisionManager& GetInstance()
	{
		static OCollisionManager CollisionManager;
		return CollisionManager;
	}
};
