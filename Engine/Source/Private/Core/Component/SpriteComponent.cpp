// Copyright deRenevo. All rights reserved.

#include "Core/Component/SpriteComponent.h"

#include "Core/Manager/SceneManager.h"

OSpriteComponent::OSpriteComponent() : OSpriteComponent("RenderSpriteComponent")
{
}

OSpriteComponent::OSpriteComponent(const std::string& name) : ORenderComponent(name)
{
	
}

OSpriteComponent::OSpriteComponent(const uint8 layer) : ORenderComponent(layer, "RenderSpriteComponent")
{
}

OSpriteComponent::~OSpriteComponent()
{
	UnloadTextureAsync();
}

void OSpriteComponent::Render(const FBox2D& cameraViewBox)
{	
	if (!GetVisible())
	{
		return;
	}

	const Texture2D* Texture = TextureManager::GetInstance().ResolveTexture(TextureHandle);
	if (!Texture)
	{
		return;
	}
	
	if (!CollisionMath::Intersect(GetWorldBox(), cameraViewBox))
	{
		return;
	}
	
	DrawTextureV(*Texture, GetWorldLocation() + GetRenderAlignment(), WHITE);
}

void OSpriteComponent::UnloadTexture() const
{
	if (!TextureHandle.IsValid())
	{
		return;
	}

	TextureManager::GetInstance().UnloadTexture(TextureHandle);
}

void OSpriteComponent::UnloadTextureAsync() const
{
	if (!TextureHandle.IsValid())
	{
		return;
	}

	TextureManager::GetInstance().UnloadTextureAsync(TextureHandle);
}

FBox2D OSpriteComponent::GetWorldBox()
{
	if (!TextureHandle.IsValid())
	{
		return FBox2D();
	}

	const Texture* Texture2D = TextureManager::GetInstance().ResolveTexture(TextureHandle);
	if (!Texture2D)
	{
		return FBox2D();
	}
	
	FVector2D Size = {static_cast<float>(Texture2D->width), static_cast<float>(Texture2D->height)};
	const FVector2D Location = GetWorldLocation();

	return {Location - Size / 2, Size};
}
