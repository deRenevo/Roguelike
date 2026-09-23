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
	UnloadTexture();
}

void OSpriteComponent::Draw(const FBox2D& cameraViewportBounds)
{
	if (!Texture2D)
	{
		return;
	}
	
	if (bIsVisible && IsTextureValid(*Texture2D) && CollisionMath::Intersect(GetWorldBox(), cameraViewportBounds))
	{
		FVector2D Location = GetWorldLocation();
		DrawTexture(*Texture2D, Location.X + SpriteAlignment.X, Location.Y + SpriteAlignment.Y, WHITE);
	}
	OSceneComponent::Draw(cameraViewportBounds);
}
