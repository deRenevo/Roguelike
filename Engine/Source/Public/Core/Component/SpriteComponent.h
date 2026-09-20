// Copyright deRenevo. All rights reserved.

#pragma once

#include <Core/Component/SceneComponent.h>

#include "Core/Manager/TextureManager.h"

class OSpriteComponent : public OSceneComponent
{
	Texture* Texture2D = nullptr;
	FVector2D SpriteAlignment = FVector2D::ZeroVector;
	bool bIsVisible = true;

protected:
	virtual void Draw() override;

public:
	OSpriteComponent();
	OSpriteComponent(const std::string& name);

	virtual ~OSpriteComponent() override;

	//setters and setters
	void SetTexture(Texture* texture)
	{
		Texture2D = texture;
	}

	void LoadTexture(const std::string& texturePath)
	{
		if (Texture2D)
		{
			OTextureManager::GetInstance().UnloadTexture(Texture2D);
		}
		
		SetTexture(OTextureManager::GetInstance().LoadTexture(texturePath));
	}
	
	void UnloadTexture()
	{
		if (!Texture2D)
		{
			return;
		}
		
		OTextureManager::GetInstance().UnloadTexture(Texture2D);
	}

	void SetSpriteAlignment(const FVector2D& spriteAlignment)
	{
		SpriteAlignment = spriteAlignment;
	}
	
	void SetIsVisible(const bool isVisible)
	{
		bIsVisible = isVisible;
	}

	Texture* GetTexture() const
	{
		return Texture2D;
	}
	
	bool IsVisible() const
	{
		return bIsVisible;
	}
};
