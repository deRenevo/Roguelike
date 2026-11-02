// Copyright deRenevo. All rights reserved.

#pragma once

#include <vector>

#include "Core/HUD/HUD.h"
#include "Core/Render/RenderLayer.h"


class ORenderComponent;
struct FBox2D;

class RenderManager
{
	std::array<std::unique_ptr<RRenderLayer>, 256> AllRenderLayers;
	std::vector<RRenderLayer*> ActiveRenderLayers;
	RenderManager() = default;

	RenderManager(const RenderManager&) = delete;
	RenderManager& operator=(const RenderManager&) = delete;
	RenderManager(RenderManager&) = delete;
	RenderManager& operator=(RenderManager&&) = delete;

public:
	void Ini();
	
	void Render(const FBox2D& cameraViewBox) const;
	void AddComponent(ORenderComponent* component, uint8 layer);
	void RemoveComponent(ORenderComponent* component) const;
	void AddLayer(std::unique_ptr<RRenderLayer> renderLayer, uint8 layerIndex);
	void RemoveLayer(RRenderLayer* renderLayer);
	
	static RenderManager& GetInstance()
	{
		static RenderManager DM;
		return DM;
	}
};
