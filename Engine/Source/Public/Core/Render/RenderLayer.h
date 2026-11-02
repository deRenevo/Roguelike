// Copyright deRenevo. All rights reserved.

#pragma once
#include "Core/Object/Object.h"

class ORenderComponent;
struct FBox2D;

class RRenderLayer : public OObject
{
	std::vector<ORenderComponent*> AllRenderComponents;
	bool bIsSortByDepthEveryFrame = false;
	bool bIsSortByDepthWhenAdded = false;
	bool bIsActiveLayer = false;
	uint8 RenderLayerIndex = 0;

public:
	virtual void Render(const FBox2D& cameraViewBox);

	virtual void OnBeginRender()
	{
	}

	virtual void OnEndRender()
	{
	}
	
	void AddComponent(ORenderComponent* component);
	void RemoveComponent(const ORenderComponent* component);

	//getters and setters 

	void SetRenderLayerIndex(const uint8 index)
	{
		RenderLayerIndex = index;
	}
	
	void SetIsActiveRenderLayer(const bool isActive)
	{
		bIsActiveLayer = isActive;
	}
	
	void SetIsSortEveryFrame(const bool isSort)
	{
		bIsSortByDepthEveryFrame = isSort;
	}
	
	void SetIsSortWhenAdded(const bool isSort)
	{
		bIsSortByDepthWhenAdded = isSort;
	}

	uint8 GetRenderLayerIndex() const
	{
		return RenderLayerIndex;
	}
	
	bool GetIsActiveRenderLayer() const
	{
		return bIsActiveLayer;
	}
	
	bool GetIsSortByDepthEveryFrame() const
	{
		return bIsSortByDepthEveryFrame;
	}
	
	bool GetIsSortWhenAdded() const
	{
		return bIsSortByDepthWhenAdded;
	}
};
