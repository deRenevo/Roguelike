// Copyright deRenevo. All rights reserved.

#pragma once

#include <Core/Component/SceneComponent.h>

#include <raylib.h>

class OSpriteComponent : public OSceneComponent
{
	Texture2D Texture = {};
	Vector2 SpriteAlignment = {0, 0};

protected:
	virtual void Draw() override;

public:
	OSpriteComponent();
	OSpriteComponent(const std::string& name);

	virtual ~OSpriteComponent() override;

	//setters
	void SetTexture(const Texture2D& texture)
	{
		Texture = texture;
	}

	void LoadTexture(const std::string& texturePath)
	{
		SetTexture(::LoadTexture(texturePath.c_str()));
	}

	void SetSpriteAlignment(const Vector2& spriteAlignment)
	{
		SpriteAlignment = spriteAlignment;
	}

	//getters
	Texture2D GetTexture() const
	{
		return Texture;
	}
};
