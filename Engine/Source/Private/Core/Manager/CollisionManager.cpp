// Copyright deRenevo. All rights reserved.

#include <Core/Manager/CollisionManager.h>

#include "Core/Actor/Actor.h"
#include "Core/Component/CollisionComponent.h"
#include "Core/Math/CollisionMath.h"

void OCollisionManager::Tick(float deltaTime)
{
	const int32 Count = CollisionComponents.size();
	
	for (int32 i = 0; i < Count; ++i)
	{
		OCollisionComponent* ComponentA = CollisionComponents[i];
		const FBox2D BoxA = ComponentA->GetWorldBox2D();
		
		for (int32 j = i + 1; j < Count; ++j)
		{
			OCollisionComponent* ComponentB = CollisionComponents[j];
			
			if (ComponentA->GetIsStatic() && ComponentB->GetIsStatic())
			{
				continue;
			}
            
			const FBox2D BoxB = ComponentB->GetWorldBox2D();
			
			if (CollisionMath::Intersect(BoxA, BoxB))
			{
				ComponentA->SetIsColliding(true);
				ComponentB->SetIsColliding(true);

				if (!ComponentA->GetIsStatic())
				{
					const FVector2D MTV = CollisionMath::MTV(BoxA, BoxB);
					ComponentA->GetOwner()->SetLocation(
						ComponentA->GetOwner()->GetLocation() + MTV
					);
				}

				if (!ComponentB->GetIsStatic())
				{
					const FVector2D MTV = CollisionMath::MTV(BoxB, BoxA);
					ComponentB->GetOwner()->SetLocation(
						ComponentB->GetOwner()->GetLocation() + MTV
					);
				}
			}
		}
	}
}

void OCollisionManager::DoTick(float deltaTime)
{
	if (GetIsPendingKill()) return;
	Tick(deltaTime);
}
