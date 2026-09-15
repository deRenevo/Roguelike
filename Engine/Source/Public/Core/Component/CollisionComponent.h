// Copyright deRenevo. All rights reserved.

#pragma once

#include <functional>

#include "Core/Component/SceneComponent.h"
#include "Core/Math/Box2D.h"
#include "Core/Utility/MulticastDelegate.h"

class OCollisionComponent : public OSceneComponent
{
	FVector2D Size = FVector2D::ZeroVector;
	FVector2D Alignment = FVector2D::ZeroVector;

	bool bIsCollidingOldFrame = false;
	bool bIsColliding = false;
	
	bool bIsStatic = false;

public:
	MulticastDelegate<> OnStartCollisionDelegate;
	MulticastDelegate<> OnCollisionDelegate;
	MulticastDelegate<> OnEndCollisionDelegate;

	//===
protected:
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	
	//getters and setters 
	void SetSize(const FVector2D& size)
	{
		Size = size;
	}

	void SetBox(const FBox2D& box2D)
	{
		Size = box2D.GetSize();
		SetLocation(box2D.GetLocation());
	}

	void SetAlignment(const FVector2D& alignment)
	{
		Alignment = alignment;
	}

	void SetIsColliding(const bool& isColliding)
	{
		bIsColliding = isColliding;
	}
	
	void SetStatic(const bool& isStatic)
	{
		bIsStatic = isStatic;
	}

	FVector2D GetSize() const
	{
		return Size;
	}

	FBox2D GetBox() const
	{
		return {GetLocation(), Size};
	}

	FBox2D GetWorldBox2D() const
	{
		return {GetWorldLocation() + Alignment, Size};
	}

	FVector2D GetAlignment() const
	{
		return Alignment;
	}

	bool GetIsColliding() const
	{
		return bIsColliding;
	}
	
	bool GetIsStatic() const
	{
		return bIsStatic;
	}
};
