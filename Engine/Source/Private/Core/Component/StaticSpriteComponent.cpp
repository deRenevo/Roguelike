// Copyright deRenevo. All rights reserved.

#include "Core/Component/StaticSpriteComponent.h"

OStaticSpriteComponent::OStaticSpriteComponent(const std::string& name) : OSceneComponent(name)
{
	std::unique_ptr<OSpriteComponent> Sprite = std::make_unique<OSpriteComponent>();
	SpriteComponent = Sprite.get();
	AddChild(std::move(Sprite));

	std::unique_ptr<OCollisionComponent> Collision = std::make_unique<OCollisionComponent>();
	CollisionComponent = Collision.get();
	Collision->SetStatic(true);
	AddChild(std::move(Collision));
}

OStaticSpriteComponent::OStaticSpriteComponent() : OStaticSpriteComponent("StaticSpriteComponent")
{
}

void OStaticSpriteComponent::UpdateSprite(const std::string& spritePath) const
{
	if (!SpriteComponent)
	{
		return;
	}

	SpriteComponent->LoadTexture(spritePath);
	if (bIsAutoSize)
	{
		AutoSize();
	}
}

void OStaticSpriteComponent::AutoSize() const
{
	if (!SpriteComponent || !CollisionComponent)
	{
		return;
	}

	CollisionComponent->SetSize({
		static_cast<float>(SpriteComponent->GetTexture()->width),
		static_cast<float>(SpriteComponent->GetTexture()->height)
	});
}


void OStaticSpriteComponent::OnAttach()
{
	OSceneComponent::OnAttach();

}

void OStaticSpriteComponent::SetAutoSize()
{
	bIsAutoSize = true;
}
