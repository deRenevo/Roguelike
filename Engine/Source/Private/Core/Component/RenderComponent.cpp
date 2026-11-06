// Copyright deRenevo. All rights reserved.

#include "Core/Component/RenderComponent.h"

#include "Core/Manager/RenderManager.h"

ORenderComponent::ORenderComponent() : OSceneComponent("SpriteComponent")
{
	
}

ORenderComponent::ORenderComponent(const std::string& name) : OSceneComponent(name)
{
	
}

ORenderComponent::ORenderComponent(const uint8 renderLayer) : ORenderComponent()
{
	RenderLayerIndex = renderLayer;
}

ORenderComponent::ORenderComponent(const uint8 renderLayer, const std::string& name) : ORenderComponent(name)
{
	RenderLayerIndex = renderLayer;
}

ORenderComponent::ORenderComponent(const uint8 renderLayer, const FVector2D& location) : ORenderComponent()
{
	SetLocation(location);
	RenderLayerIndex = renderLayer;
}

ORenderComponent::ORenderComponent(const uint8 renderLayer, const FVector2D& location, const std::string& name) : ORenderComponent(name)
{
	SetLocation(location);
	RenderLayerIndex = renderLayer;
}

ORenderComponent::~ORenderComponent()
{
	RenderManager::GetInstance().RemoveComponent(this);
}

void ORenderComponent::OnAttach()
{
	OSceneComponent::OnAttach();
	RenderManager::GetInstance().AddComponent(this, RenderLayerIndex);
}

void ORenderComponent::OnDetach()
{
	OSceneComponent::OnDetach();
	RenderManager::GetInstance().RemoveComponent(this);
}
