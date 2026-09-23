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
	
	bool bIsStatic = true;

public:
	MulticastDelegate<> OnStartCollisionDelegate;
	MulticastDelegate<> OnCollisionDelegate;
	MulticastDelegate<> OnEndCollisionDelegate;

	//===
protected:
	virtual void Tick(float deltaTime) override;
	virtual void Draw(const FBox2D& cameraViewportBounds) override;

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
		FVector2D Location = GetLocation();
		return {FVector2D(Location.X + Size.X, Location.Y + Size.Y/2), Size};
	}

	FBox2D GetWorldBox2D() const
	{
		FVector2D Location = GetWorldLocation();
		return {FVector2D(Location.X + Size.X/2 + Alignment.X, Location.Y + Size.Y/2 + Alignment.Y), Size};
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
