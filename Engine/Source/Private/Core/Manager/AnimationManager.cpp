// Copyright deRenevo. All rights reserved.

#include "Core/Manager/AnimationManager.h"

#include <ostream>

FAnimationHandle AnimationManager::LoadAnimation(const std::string& texturePath, const uint8 countFrame, const float updateFrameTime = 1.f)
{
	if (const std::unordered_map<std::string, unsigned>::iterator& it = AnimationMap.find(texturePath); it != AnimationMap.end())
	{
		const uint32 Index = it->second;
		++AnimationSlots[Index]->CountUsing;
		return {Index, AnimationSlots[Index]->Generation};
	}

	uint32 Index;

	if (!FreeIndex.empty())
	{
		Index = FreeIndex.back();
		FreeIndex.pop_back();
	}
	else
	{
		AnimationSlots.emplace_back(std::make_unique<FAnimationSlot>());
		Index = static_cast<uint32>(AnimationSlots.size() - 1);
	}

	const FTextureHandle TextureHandle = TextureManager::GetInstance().LoadTexture(texturePath);

	if (!TextureHandle.IsValid())
	{
		return {};
	}

	std::unique_ptr<FAnimationClip> AnimationClip = std::make_unique<FAnimationClip>();
	AnimationClip->TextureHandle = TextureHandle;

	const Texture2D* Texture = TextureManager::GetInstance().ResolveTexture(TextureHandle);

	AnimationClip->FrameWidth = Texture->width / countFrame;
	AnimationClip->FrameHeight = Texture->height;
	AnimationClip->FrameCount = countFrame;
	AnimationClip->UpdateFrameTime = updateFrameTime;

	FAnimationSlot* AnimationSlot = AnimationSlots[Index].get();
	AnimationSlot->AnimationClip = std::move(AnimationClip);
	AnimationSlot->CountUsing = 1;
	AnimationMap[texturePath] = Index;

	return {Index, AnimationSlot->Generation};
}

FAnimationClip* AnimationManager::ResolveAnimationClip(const FAnimationHandle animationHandle) const
{
	return AnimationSlots[animationHandle.Index]->Generation == animationHandle.Generation ? AnimationSlots[animationHandle.Index]->AnimationClip.get() : nullptr;
}

void AnimationManager::UnloadAnimation(const FAnimationHandle animationHandle)
{
	if (!animationHandle.IsValid())
	{
		return;
	}

	FAnimationSlot* AnimationSlot = AnimationSlots[animationHandle.Index].get();
	AnimationSlot->CountUsing--;

	if (AnimationSlot->CountUsing == 0)
	{
		TextureManager::GetInstance().UnloadTextureAsync(AnimationSlots[animationHandle.Index]->
														AnimationClip->TextureHandle);
		AnimationSlot->AnimationClip.reset();
		++AnimationSlot->Generation;
		FreeIndex.push_back(animationHandle.Index);
	}
}

void AnimationManager::ClearAnimationMap()
{
	for (const std::unique_ptr<FAnimationSlot>& AnimationSlot : AnimationSlots)
	{
		if (AnimationSlot->AnimationClip)
		{
			TextureManager::GetInstance().UnloadTextureAsync(AnimationSlot->AnimationClip->TextureHandle);
		}
	}
	
	AnimationSlots.clear();
	FreeIndex.clear();
	AnimationMap.clear();
}
