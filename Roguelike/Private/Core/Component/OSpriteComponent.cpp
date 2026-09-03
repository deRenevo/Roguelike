// Copyright deRenevo. All rights reserved.

#include "Core/Component/OSpriteComponent.h"

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
		::UnloadTexture(Texture);
	}
}

void OSpriteComponent::SetTexture(const Texture2D& texture)
{
	Texture = texture;
}

void OSpriteComponent::LoadTexture(const std::string& texturePath)
{
	SetTexture(::LoadTexture(texturePath.c_str()));
}

void OSpriteComponent::SetSpriteAlignment(const Vector2& spriteAlignment)
{
	SpriteAlignment = spriteAlignment;
}

Texture2D OSpriteComponent::GetTexture() const
{
	return Texture;
}

void OSpriteComponent::Draw()
{
	if (IsTextureValid(Texture))
	{
		Vector2 Location = GetWorldLocation();
		DrawTexture(Texture, Location.x + SpriteAlignment.x, Location.y + SpriteAlignment.y, WHITE);
	}
	OSceneComponent::Draw();
}
