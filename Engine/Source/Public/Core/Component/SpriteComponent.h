// Copyright deRenevo. All rights reserved.

#pragma once

#include <Core/Component/SceneComponent.h>

class OSpriteComponent : public OSceneComponent
{
	Texture2D Texture = {};
	FVector2D SpriteAlignment = FVector2D::ZeroVector;
	bool bIsVisible = true;

protected:
	virtual void Draw() override;

public:
	OSpriteComponent();
	OSpriteComponent(const std::string& name);

	virtual ~OSpriteComponent() override;

	//setters and setters
	void SetTexture(const Texture2D& texture)
	{
		Texture = texture;
	}

	void LoadTexture(const std::string& texturePath)
	{
		SetTexture(::LoadTexture(texturePath.c_str()));
	}

	void SetSpriteAlignment(const FVector2D& spriteAlignment)
	{
		SpriteAlignment = spriteAlignment;
	}
	
	void SetIsVisible(const bool isVisible)
	{
		bIsVisible = isVisible;
	}

	Texture2D GetTexture() const
	{
		return Texture;
	}
	
	bool IsVisible() const
	{
		return bIsVisible;
	}
};
