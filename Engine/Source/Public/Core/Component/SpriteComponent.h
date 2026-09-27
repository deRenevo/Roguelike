// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Component/SceneComponent.h"

#include "Core/Manager/TextureManager.h"
#include "Core/Math/Box2D.h"

class OSpriteComponent : public OSceneComponent
{
	FTextureHandle TextureHandle;
	FVector2D SpriteAlignment = FVector2D::ZeroVector;
	bool bIsVisible = true;

protected:
	virtual void Draw(const FBox2D& cameraViewportBounds) override;

public:
	OSpriteComponent();
	OSpriteComponent(const std::string& name);

	virtual ~OSpriteComponent() override;

	//setters and setters

	void LoadTexture(const std::string& texturePath)
	{
		if (TextureHandle.IsValid())
		{
			TextureManager::GetInstance().UnloadTextureAsync(TextureHandle);
		}

		TextureHandle = TextureManager::GetInstance().LoadTexture(texturePath);
	}

	void UnloadTexture() const
	{
		if (!TextureHandle.IsValid())
		{
			return;
		}

		TextureManager::GetInstance().UnloadTexture(TextureHandle);
	}

	void UnloadTextureAsync() const
	{
		if (!TextureHandle.IsValid())
		{
			return;
		}

		TextureManager::GetInstance().UnloadTextureAsync(TextureHandle);
	}

	void SetSpriteAlignment(const FVector2D& spriteAlignment)
	{
		SpriteAlignment = spriteAlignment;
	}

	void SetIsVisible(const bool isVisible)
	{
		bIsVisible = isVisible;
	}

	const FTextureHandle& GetTextureHandle() const
	{
		return TextureHandle;
	}

	const Texture* GetTexture() const
	{
		return TextureManager::GetInstance().ResolveTexture(TextureHandle);
	}

	FBox2D GetWorldBox() const
	{
		if (!TextureHandle.IsValid())
		{
			return FBox2D();
		}
		
		Texture* Texture2D = TextureManager::GetInstance().ResolveTexture(TextureHandle);
		FVector2D Size = {static_cast<float>(Texture2D->width), static_cast<float>(Texture2D->height)};
		FVector2D Location = GetWorldLocation();

		return {Location - Size / 2, Size};
	}

	bool IsVisible() const
	{
		return bIsVisible;
	}
};
