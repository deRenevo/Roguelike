// Copyright deRenevo. All rights reserved.

#pragma once
#include "Core/Component/SceneComponent.h"
#include "Core/Math/CollisionMath.h"

class ORenderComponent : public OSceneComponent
{
	FVector2D RenderAlignment = FVector2D::ZeroVector;
	float DepthKey = 0.f; // for z-buffer 
	bool bIsVisible = true;
	uint32 RegistryRenderIndex = UINT32_MAX; // for fast earth from draw manager.
	uint8 RenderLayerIndex = 64; // default layer is floor tile
	
protected:
	//virtual void OnRegisterScene(); 
	//virtual void OnUnregisterScene();
	
public:
	ORenderComponent();
	ORenderComponent(const std::string& name);
	ORenderComponent(const uint8 renderLayer);
	ORenderComponent(const uint8 renderLayer, const std::string& name);
	ORenderComponent(const uint8 renderLayer, const FVector2D& location);
	ORenderComponent(const uint8 renderLayer, const FVector2D& location, const std::string& name);
	
	virtual ~ORenderComponent() override;
	
	virtual void Render(const FBox2D& cameraViewBox) = 0;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	
	virtual FBox2D GetWorldBox() = 0;
	
	// Setters and Getters  
	void SetDepthKey(const float depthKey)
	{
		DepthKey = depthKey;
	}
	
	void SetVisible(const bool visible)
	{
		bIsVisible = visible;
	}
	
	void SetRenderAlignment(const FVector2D& renderAlignment)
	{
		RenderAlignment = renderAlignment;
	}
	
	void SetRegistryRenderIndex(const uint32 index)
	{
		if (index == UINT32_MAX)
		{
			printf("index is not correct\n");
			return;
		}
		RegistryRenderIndex = index;
	}
	
	void SetRenderLayer(const uint8 renderLayer)
	{
		RenderLayerIndex = renderLayer;
	}
	
	float GetDepthKey() const 
	{
		return DepthKey;
	}
	
	bool GetVisible() const
	{
		return bIsVisible;
	}
	
	FVector2D GetRenderAlignment() const
	{
		return RenderAlignment;
	}
	
	uint32 GetRegistryRenderIndex() const
	{
		return RegistryRenderIndex;
	}
	
	uint8 GetRenderLayer() const
	{
		return RenderLayerIndex;
	}
};

