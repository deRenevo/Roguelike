// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Component/RenderComponent.h"
#include "Core/Manager/TextureManager.h"

class ORenderSpriteComponent : public ORenderComponent
{
	FTextureHandle TextureHandle;
protected:
	void UnloadTexture() const;
	void UnloadTextureAsync() const;
	
public:
	ORenderSpriteComponent();
	ORenderSpriteComponent(const std::string& name);
	ORenderSpriteComponent(const uint8 layer);
	
	virtual ~ORenderSpriteComponent() override;
	
	virtual void Render(const FBox2D& cameraViewBox) override;
	
	void LoadTexture(const std::string& texturePath)
	{
		if (TextureHandle.IsValid())
		{
			TextureManager::GetInstance().UnloadTextureAsync(TextureHandle);
		}

		TextureHandle = TextureManager::GetInstance().LoadTexture(texturePath);
	}
	
	// Setters and Getters
	
	FBox2D GetWorldBox() override;
	
	const Texture* GetTexture() const // Can return nullptr
	{
		return TextureManager::GetInstance().ResolveTexture(TextureHandle);
	}
	
	const FTextureHandle& GetTextureHandle() const
	{
		return TextureHandle;
	}
};
