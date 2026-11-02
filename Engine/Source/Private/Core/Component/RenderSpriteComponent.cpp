// Copyright deRenevo. All rights reserved.

#include "Core/Component/RenderSpriteComponent.h"

#include "Core/Manager/SceneManager.h"

void ORenderSpriteComponent::Render(const FBox2D& cameraViewBox)
{	
	if (!GetVisible())
	{
		return;
	}
	
	Texture2D* Texture = TextureManager::GetInstance().ResolveTexture(TextureHandle);
	if (!Texture)
	{
		return;
	}
	
	if (!CollisionMath::Intersect(GetWorldBox(), cameraViewBox))
	{
		return;
	}
	
	FVector2D Location = GetWorldLocation();
	DrawTexture(*Texture, Location.X + GetRenderAlignment().X, Location.Y + GetRenderAlignment().Y, WHITE);
}

void ORenderSpriteComponent::UnloadTexture() const
{
	if (!TextureHandle.IsValid())
	{
		return;
	}

	TextureManager::GetInstance().UnloadTexture(TextureHandle);
}

void ORenderSpriteComponent::UnloadTextureAsync() const
{
	if (!TextureHandle.IsValid())
	{
		return;
	}

	TextureManager::GetInstance().UnloadTextureAsync(TextureHandle);
}


ORenderSpriteComponent::ORenderSpriteComponent() : ORenderSpriteComponent("RenderSpriteComponent")
{
}

ORenderSpriteComponent::ORenderSpriteComponent(const std::string& name) : ORenderComponent(name)
{
	
}

ORenderSpriteComponent::ORenderSpriteComponent(const uint8 layer) : ORenderSpriteComponent("RenderSpriteComponent")
{
	SetRenderLayer(layer);
}

ORenderSpriteComponent::~ORenderSpriteComponent()
{
	UnloadTextureAsync();
}

FBox2D ORenderSpriteComponent::GetWorldBox()
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
