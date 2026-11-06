// Copyright deRenevo. All rights reserved.

#include "Core/Manager/RenderManager.h"

#include "Core/Component/RenderComponent.h"
#include "Core/HUD/HUD.h"
#include "Core/Render/RenderLayer.h"

void RenderManager::Ini()
{
	{
		std::unique_ptr<RRenderLayer> RenderLayer = std::make_unique<RRenderLayer>();
		AddLayer(std::move(RenderLayer), 64); // Bose layer with not sort (for static floor)
	}
	
	{
		std::unique_ptr<RRenderLayer> RenderLayer = std::make_unique<RRenderLayer>();
		RenderLayer->SetIsSortEveryFrame(true);
		AddLayer(std::move(RenderLayer), 128); // Base layer with sort every frame for base actor (Pawn, build, environment)
	}
	
}

void RenderManager::Render(const FBox2D& cameraViewBox) const
{
	for (const auto& Layer : AllRenderLayers)
	{
		if (Layer == nullptr)
		{
			continue;
		}
		Layer->Render(cameraViewBox);
	}
}

void RenderManager::AddLayer(std::unique_ptr<RRenderLayer> renderLayer, uint8 layerIndex)
{
	if (renderLayer == nullptr)
	{
		printf("Error render layer with %i index is nullptr\n", layerIndex);
		return;
	}
	
	if (renderLayer->GetIsActiveRenderLayer())
	{
		printf("Error render layer with %i index is already active\n", layerIndex);
		return;
	}
	
	if (layerIndex > 256)
	{
		printf("Error render layer with %i index is out of range\n", layerIndex);
		return;
	}
	
	if (AllRenderLayers[layerIndex] != nullptr)
	{
		printf("Error render layer with %i index it`s exist\n", layerIndex);
		return;
	}
	
	AllRenderLayers[layerIndex] = std::move(renderLayer);
	
	const auto It = std::ranges::lower_bound(ActiveRenderLayers, AllRenderLayers[layerIndex].get(),
		[](const RRenderLayer* layerA, const RRenderLayer* layerB)
		{
			return layerA->GetRenderLayerIndex() < layerB->GetRenderLayerIndex();
		});
	
	ActiveRenderLayers.insert(It, AllRenderLayers[layerIndex].get());
	AllRenderLayers[layerIndex]->SetRenderLayerIndex(layerIndex);
	AllRenderLayers[layerIndex]->SetIsActiveRenderLayer(true);
}

void RenderManager::RemoveLayer(RRenderLayer* renderLayer)
{
	if (renderLayer == nullptr)
	{
		printf("Error render layer is nullptr\n");
		return;
	}
	
	if (!renderLayer->GetIsActiveRenderLayer())
	{
		printf("Error render layer with %i index is not active layer\n", renderLayer->GetRenderLayerIndex());
		return;
	}
	
	uint8 LayerIndex = renderLayer->GetRenderLayerIndex();
	
	if (AllRenderLayers[LayerIndex] == nullptr)
	{
		printf("Error render layer in array with %i index is nullptr\n", LayerIndex);
		return;
	}
	
	if (AllRenderLayers[LayerIndex].get() != renderLayer)
	{
		printf("Error render layer with %i index not equal in array\n", LayerIndex);
		return;
	}
	
	std::erase_if(ActiveRenderLayers, [renderLayer](const RRenderLayer* a)
	{
		return renderLayer == a; 
	});
	AllRenderLayers[LayerIndex].reset();
}

void RenderManager::AddComponent(ORenderComponent* component, const uint8 layer)
{
	if (!component)
	{
		printf("Error render component is nullptr\n");
		return;
	}
	
	if (AllRenderLayers[layer] == nullptr)
	{
		printf("Error render layer with %i index is nullptr\n", layer);
		
		if (AllRenderLayers[64] != nullptr)
		{
			printf("Error render layer with %i index is nullptr. Before component added to %i layer\n", layer, 64);
			AllRenderLayers[64]->AddComponent(component);
			return;
		}
		
		printf("Critical error Render layer with %i index is nullptr\n", 64);
		return;
	}
	
	AllRenderLayers[layer]->AddComponent(component);
}

void RenderManager::RemoveComponent(const ORenderComponent* component) const
{
	if (component == nullptr)
	{
		printf("Error render component is nullptr\n");
		return;
	}
	
	if (AllRenderLayers[component->GetRenderLayer()] == nullptr)
	{
		printf("Error render layer with %i index is nullptr\n", component->GetRenderLayer());
		return;
	}
	
	AllRenderLayers[component->GetRenderLayer()]->RemoveComponent(component);
}

void RenderManager::ClearAll()
{        
	for (auto& layer : AllRenderLayers)
	{
		if (layer)
		{
			layer->ClearAll();
		}
	}
}