// Copyright deRenevo. All rights reserved.

#pragma once

#include <functional>

#include "Core/Component/SceneComponent.h"
#include "Core/Math/Box2D.h"

class OCollisionComponent : public OSceneComponent
{
	FVector2D Size = FVector2D::ZeroVector;
	FVector2D Alignment = FVector2D::ZeroVector;

	bool bIsCollidingOldFrame = false;
	bool bIsColliding = false;
	
	bool bIsStatic = false;

	//hardCODE 

	std::vector<std::function<void()>> OnStartCollisionCollBackFunctions;
	std::vector<std::function<void()>> OnCollisionCollBackFunctions;
	std::vector<std::function<void()>> OnEndCollisionCollBackFunctions;

	//===
protected:
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	
	void AddOnStartCollisionCollBackFunction(const std::function<void()>& function)
	{
		OnStartCollisionCollBackFunctions.push_back(function);
	}
	
	void AddOnCollisionCollBackFunction(const std::function<void()>& function)
	{
		OnCollisionCollBackFunctions.push_back(function);
	}
	
	void AddOnEndCollisionCollBackFunction(const std::function<void()>& function)
	{
		OnEndCollisionCollBackFunctions.push_back(function);
	}
	
	//not remove function because not ptr 

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
