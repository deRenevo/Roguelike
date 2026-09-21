// Copyright deRenevo. All rights reserved.

#pragma once
#include "CollisionComponent.h"
#include "Core/Component/SpriteComponent.h"


class OStaticSpriteComponent : public OSceneComponent
{
	OSpriteComponent* SpriteComponent = nullptr;
	OCollisionComponent* CollisionComponent = nullptr;

	bool bIsAutoSize = true;
	FVector2D Alignment = FVector2D::ZeroVector;

public:
	OStaticSpriteComponent(const std::string& name);
	OStaticSpriteComponent();

	void UpdateSprite(const std::string& spritePath) const;
	void AutoSize() const;

	//setters and getters
	void SetCollisionSize(const FVector2D& size)
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
			SpriteComponent->SetSpriteAlignment(alignment);
		}
    
		if (CollisionComponent)
		{
			CollisionComponent->SetAlignment(alignment);
		}
	}

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

	void SetAutoSize(bool isAutoSize)
	{
		bIsAutoSize = isAutoSize;
	}

	virtual void OnAttach() override;

	void SetAutoSize();
};
