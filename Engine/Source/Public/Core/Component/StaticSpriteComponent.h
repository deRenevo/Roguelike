// Copyright deRenevo. All rights reserved.

#pragma once

#include "CollisionComponent.h"
#include "Core/Component/RenderSpriteComponent.h"

class OStaticSpriteComponent : public OSceneComponent
{
	ORenderSpriteComponent* SpriteComponent = nullptr;
	OCollisionComponent* CollisionComponent = nullptr;

	bool bIsAutoSize = true;
	FVector2D Alignment = FVector2D::ZeroVector;

public:
	OStaticSpriteComponent(const std::string& name, uint8 layer = 64);
	OStaticSpriteComponent(const uint8 layer);
	OStaticSpriteComponent();

	void UpdateSprite(const std::string& spritePath) const;
	void AutoSize() const;

	//setters and getters
	void SetCollisionSize(const FVector2D& size) const
	{
		if (CollisionComponent)
		{
			CollisionComponent->SetSize(size);
		}
	}

	void SetAlignment(const FVector2D& alignment)
	{
		Alignment = alignment;

		if (SpriteComponent)
		{
			SpriteComponent->SetRenderAlignment(alignment);
		}
    
		if (CollisionComponent)
		{
			CollisionComponent->SetAlignment(alignment);
		}
	}

	ORenderSpriteComponent* GetSpriteComponent() const
	{
		return SpriteComponent;
	}

	OCollisionComponent* GetCollisionComponent() const
	{
		return CollisionComponent;
	}

	FVector2D GetAlignment() const
	{
		return Alignment;
	}

	void SetAutoSize(bool isAutoSize)
	{
		bIsAutoSize = isAutoSize;
	}

	virtual void OnAttach() override;

	void SetAutoSize();
};
