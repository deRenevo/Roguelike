// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Component/SceneComponent.h"

#include "Core/Component/CollisionComponent.h"
#include "Core/Component/SpriteComponent.h"

class OStaticSpriteComponent : public OSceneComponent
{
	OSpriteComponent* SpriteComponent = nullptr;
	OCollisionComponent* CollisionComponent = nullptr;

	bool bIsAutoSize = true;
	FVector2D Alignment = FVector2D::ZeroVector;

public:
	explicit OStaticSpriteComponent(const std::string& name, uint8 layer = 64);
	explicit OStaticSpriteComponent(uint8 layer);
	OStaticSpriteComponent();

	void UpdateSprite(const std::string& spritePath) const;
	void AutoSize() const;

	//setters
	void SetAutoSize();

	void SetAutoSize(const bool isAutoSize)
	{
		bIsAutoSize = isAutoSize;
	}

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

	//getters
	OSpriteComponent* GetSpriteComponent() const
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
};
