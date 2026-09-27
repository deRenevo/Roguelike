// Copyright deRenevo. All rights reserved.

#include "Core/Component/SpriteComponent.h"

#include "Core/Math/CollisionMath.h"

OSpriteComponent::OSpriteComponent() : OSpriteComponent("SpriteComponent")
{
}

OSpriteComponent::OSpriteComponent(const std::string& name) : OSceneComponent(name)
{
}

OSpriteComponent::~OSpriteComponent()
{
	UnloadTextureAsync();
}

void OSpriteComponent::Draw(const FBox2D& cameraViewportBounds)
{
	if (bIsVisible && CollisionMath::Intersect(GetWorldBox(), cameraViewportBounds))
	{
		Texture2D* Texture = TextureManager::GetInstance().ResolveTexture(TextureHandle);
		if (!Texture)
		{
			return;
		}

		FVector2D Location = GetWorldLocation();
		DrawTexture(*Texture, Location.X + SpriteAlignment.X, Location.Y + SpriteAlignment.Y, WHITE);	
		
	}
	OSceneComponent::Draw(cameraViewportBounds);
}
