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
	if (IsTextureValid(Texture))
	{
		UnloadTexture(Texture);
	}
}

void OSpriteComponent::Draw()
{
	if (IsTextureValid(Texture))
	{
		FVector2D Location = GetWorldLocation();
		DrawTexture(Texture, Location.X + SpriteAlignment.X, Location.Y + SpriteAlignment.Y, WHITE);
	}
	OSceneComponent::Draw();
}
