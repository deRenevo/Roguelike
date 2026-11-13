// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Component/RenderComponent.h"

#include "Core/Manager/TextureManager.h"

class OSpriteComponent : public ORenderComponent
{
	FTextureHandle TextureHandle;

protected:
	void UnloadTexture() const;
	void UnloadTextureAsync() const;

public:
	OSpriteComponent();
	explicit OSpriteComponent(const std::string& name);
	explicit OSpriteComponent(const uint8 layer);

	virtual ~OSpriteComponent() override;

	virtual void Render(const FBox2D& cameraViewBox) override;

	void LoadTexture(const std::string& texturePath)
	{
		if (TextureHandle.IsValid())
		{
			TextureManager::GetInstance().UnloadTextureAsync(TextureHandle);
		}

		TextureHandle = TextureManager::GetInstance().LoadTexture(texturePath);
	}

	//Getters
	FBox2D GetWorldBox() override;

	const Texture2D* GetTexture() const // Can return nullptr
	{
		return TextureManager::GetInstance().ResolveTexture(TextureHandle);
	}

	const FTextureHandle& GetTextureHandle() const
	{
		return TextureHandle;
	}
};
