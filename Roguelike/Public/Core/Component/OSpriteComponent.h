// Copyright deRenevo. All rights reserved.

#pragma once

#include <Core/Component/SceneComponent.h>

#include <raylib.h>

class OSpriteComponent : public OSceneComponent
{
	Texture2D Texture = {};
	Vector2 SpriteAlignment = {0,0}; 
protected:
	virtual void Draw() override;
	
public:
	OSpriteComponent();
	OSpriteComponent(const std::string& name);
	
	virtual ~OSpriteComponent() override;
	
	void SetTexture(const Texture2D& texture);
	void LoadTexture(const std::string& texturePath);
	
	void SetSpriteAlignment(const Vector2& spriteAlignment);
	
	Texture2D GetTexture() const;
};
