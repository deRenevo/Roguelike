// Copyright deRenevo. All rights reserved.

#include "Core/Component/AnimationComponent.h"

OAnimationComponent::OAnimationComponent() : OAnimationComponent("AnimationComponent")
{
}

OAnimationComponent::OAnimationComponent(const std::string& name) : ORenderComponent(name)
{
}

OAnimationComponent::OAnimationComponent(const uint8 layer) : ORenderComponent(layer)
{
}

OAnimationComponent::OAnimationComponent(const uint8 layer, const std::string& name) : ORenderComponent(layer, name)
{
}

OAnimationComponent::~OAnimationComponent()
{
	AnimationManager::GetInstance().UnloadAnimation(AnimationHandle);
}

void OAnimationComponent::Render(const FBox2D& cameraViewBox)
{
	if (!GetVisible())
	{
		return;
	}

	const FAnimationClip* AnimationClip = AnimationManager::GetInstance().ResolveAnimationClip(AnimationHandle);

	if (!AnimationClip)
	{
		return;
	}

	const Texture2D* Texture = TextureManager::GetInstance().ResolveTexture(AnimationClip->TextureHandle);

	if (!Texture)
	{
		return;
	}

	if (!CollisionMath::Intersect(GetWorldBox(), cameraViewBox))
	{
		return;
	}

	DrawTextureRec(*Texture, AnimationClip->GetFrameBox(CorrectFrameCount),
		GetWorldLocation() + GetRenderAlignment(), WHITE); // if needing mirror update to fn DrawTexturePro() <- RayLib
}

void OAnimationComponent::Tick(float deltaTime)
{
	ORenderComponent::Tick(deltaTime);

	if (const FAnimationClip* AnimationClip = AnimationManager::GetInstance().ResolveAnimationClip(AnimationHandle); UpdateFrameTime < AnimationClip->UpdateFrameTime)
	{
		UpdateFrameTime += deltaTime;
	}
	else
	{
		UpdateFrameTime = 0.f;
		CorrectFrameCount = AnimationClip->FrameCount <= CorrectFrameCount ? 1 : ++CorrectFrameCount;
	}
}

void OAnimationComponent::LoadTexture(const std::string& path, const uint8 countFrame, const float updateFrameTime)
{
	if (AnimationHandle.IsValid())
	{
		AnimationManager::GetInstance().UnloadAnimation(AnimationHandle);
	}
		
	AnimationHandle = AnimationManager::GetInstance().LoadAnimation(path, countFrame, updateFrameTime);
}

void OAnimationComponent::UnloadTexture() const
{
	if (!AnimationHandle.IsValid())
	{
		return;
	}
	
	AnimationManager::GetInstance().UnloadAnimation(AnimationHandle);
}

FBox2D OAnimationComponent::GetWorldBox()
{
	if (!AnimationHandle.IsValid())
	{
		return FBox2D();
	}
	
	const FAnimationClip* AnimationClip = AnimationManager::GetInstance().ResolveAnimationClip(AnimationHandle);
	if (!AnimationClip)
	{
		return FBox2D();
	}
	
	FVector2D Size = {static_cast<float>(AnimationClip->FrameWidth), static_cast<float>(AnimationClip->FrameHeight)};
	const FVector2D Location = GetWorldLocation();
	
	return {Location - Size / 2, Size};
}
