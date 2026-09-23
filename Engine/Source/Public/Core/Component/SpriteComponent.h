// Copyright deRenevo. All rights reserved.

#pragma once

#include <Core/Component/SceneComponent.h>

#include "Core/Manager/TextureManager.h"
#include "Core/Math/Box2D.h"

class OSpriteComponent : public OSceneComponent
{
	Texture* Texture2D = nullptr;
	FVector2D SpriteAlignment = FVector2D::ZeroVector;
	bool bIsVisible = true;

protected:
	virtual void Draw(const FBox2D& cameraViewportBounds) override;

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
			TextureManager::GetInstance().UnloadTexture(Texture2D);
		}
		
		SetTexture(TextureManager::GetInstance().LoadTexture(texturePath));
	}
	
	void UnloadTexture()
	{
		if (!Texture2D)
		{
			return;
		}
		
		TextureManager::GetInstance().UnloadTexture(Texture2D);
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
	
	FBox2D GetWorldBox() const
	{
		FVector2D Size = {static_cast<float>(Texture2D->width), static_cast<float>(Texture2D->height)};
		FVector2D Location = GetWorldLocation();
		
		return {Location - Size/2, Size};
	}
	
	bool IsVisible() const
	{
		return bIsVisible;
	}
};
