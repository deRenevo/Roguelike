// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Component/RenderComponent.h"

#include "Core/Manager/AnimationManager.h"

class OAnimationComponent : public ORenderComponent
{
	FAnimationHandle AnimationHandle;
	uint8 CorrectFrameCount = 1;
	float UpdateFrameTime = 0.f; // Time frame updates animation (Seconds)
	float AnimationUpdateTime = 0.f;

protected:
	void UnloadTexture() const;
	virtual void Tick(float deltaTime) override;

public:
	OAnimationComponent();
	explicit OAnimationComponent(const std::string& name);
	explicit OAnimationComponent(uint8 layer);
	OAnimationComponent(uint8 layer, const std::string& name);

	virtual ~OAnimationComponent() override;

	virtual void Render(const FBox2D& cameraViewBox) override;

	void LoadTexture(const std::string& path, uint8 countFrame, float animationUpdateTime);

	// setters
	void SetUpdateFrameTime(const float animationUpdateTime)
	{
		AnimationUpdateTime = animationUpdateTime;
	}
	
	// getters
	FBox2D GetWorldBox() override;
	
	float GetAnimationUpdateTime() const
	{
		return AnimationUpdateTime;
	}
	
	const FAnimationHandle& GetAnimationHandle() const
	{
		return AnimationHandle;
	}
};
