// Copyright deRenevo. All rights reserved.

#include "Core/Component/SpriteComponent.h"

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

void OSpriteComponent::Draw()
{
	if (!Texture2D)
	{
		return;
	}
	
	if (bIsVisible && IsTextureValid(*Texture2D))
	{
		FVector2D Location = GetWorldLocation();
		DrawTexture(*Texture2D, Location.X + SpriteAlignment.X, Location.Y + SpriteAlignment.Y, WHITE);
	}
	OSceneComponent::Draw();
}
