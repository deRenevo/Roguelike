// Copyright deRenevo. All rights reserved.

#pragma once

#include "TextureManager.h"
#include "Core/Math/Box2D.h"

struct FAnimationHandle
{
	uint32 Index = UINT32_MAX;
	uint32 Generation = 0;

	inline bool IsValid() const;
};

struct FAnimationClip
{
	FTextureHandle TextureHandle;
	uint16 FrameWidth = 0;
	uint16 FrameHeight = 0;
	uint16 FrameCount = 0;
	float UpdateFrameTime = 10;

	FBox2D GetFrameBox(const uint8 frameCount) const
	{
		return {static_cast<float>(frameCount * FrameWidth), 0.f, static_cast<float>(FrameHeight),
				static_cast<float>(FrameHeight)};
	}
};

struct FAnimationSlot
{
	std::unique_ptr<FAnimationClip> AnimationClip;
	uint32 CountUsing = 0;
	uint32 Generation = 0;
};

class AnimationManager
{
	std::vector<std::unique_ptr<FAnimationSlot>> AnimationSlots;
	std::vector<uint32> FreeIndex;
	std::unordered_map<std::string, uint32> AnimationMap; // Path to file and index the slot

public:
	FAnimationHandle LoadAnimation(const std::string& texturePath, uint8 countFrame, float updateFrameTime);
	FAnimationClip* ResolveAnimationClip(FAnimationHandle animationHandle) const;
	void UnloadAnimation(FAnimationHandle animationHandle);
	void ClearAnimationMap();

	bool IsHandleValid(const FAnimationHandle animationHandle) const
	{
		if (animationHandle.Index >= AnimationSlots.size())
		{
			return false;
		}

		return AnimationSlots[animationHandle.Index]->Generation == animationHandle.Generation;
	}

	static AnimationManager& GetInstance()
	{
		static AnimationManager AM;
		return AM;
	}
};

bool FAnimationHandle::IsValid() const
{
	return AnimationManager::GetInstance().IsHandleValid(*this);
}

