// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Component/SceneComponent.h"
#include "Core/Math/Box2D.h"


class OCameraComponent : public OSceneComponent
{
	//Camera2D Camera; // X Y is Comp location
	FVector2D Offset = FVector2D::ZeroVector;  //in constructor Target Screen size/2 
	float Zoom = 1.0f;
	float Rotation = 0.f;

public:
	OCameraComponent();
	OCameraComponent(const std::string& name);
	virtual ~OCameraComponent() override = default;

	//setters

	void SetZoom(const float& zoom)
	{
		Zoom = zoom;
	}

	void SetRotation(const float& rotation)
	{
		Rotation = rotation;
	}

	void SetOffset(const FVector2D& offset)
	{
		Offset = offset;
	}

	//getters

	Camera2D GetCamera() const
	{
		Camera2D Camera;
		Camera.offset = Offset;
		Camera.rotation = Rotation;
		Camera.target = GetWorldLocation();
		Camera.zoom = Zoom;

		return Camera;
	}
	
	FBox2D GetViewBox() const
	{
		const float ScreenWidth = static_cast<float>(GetScreenWidth());
		const float ScreenHeight = static_cast<float>(GetScreenHeight());
		
		FVector2D Center = GetWorldLocation();
		
		FVector2D Size(ScreenWidth / Zoom * 1.4, ScreenHeight / Zoom * 1.4); // for not visiting breaks in drawing at the corners
    
		return FBox2D(Center, Size);
	}
};