// Copyright deRenevo. All rights reserved.

#include "Core/Render/RenderLayer.h"

#include "Core/Component/RenderComponent.h"

void RRenderLayer::Render(const FBox2D& cameraViewBox)
{
	if (bIsSortByDepthEveryFrame)
	{
		std::ranges::stable_sort(AllRenderComponents,
			[](const ORenderComponent* componentA, const ORenderComponent* componentB)
			{
				return componentA->GetWorldLocation().Y + componentA->GetDepthKey() <
					   componentB->GetWorldLocation().Y + componentB->GetDepthKey();
			});

		uint32 CurrentIndex = 0;
		for (auto* Component : AllRenderComponents)
		{
			if (!Component)
			{
				printf("Critical error component is nullptr\n");
				return;	
			}
			
			Component->SetRegistryRenderIndex(CurrentIndex);
			CurrentIndex++;
		}
	}

	for (const auto& Component : AllRenderComponents)
	{
		Component->Render(cameraViewBox);
	}
}

void RRenderLayer::AddComponent(ORenderComponent* component)
{
	if (!component)
	{
		printf("Error component is nullptr\n");
		return;
	}

	if (AllRenderComponents.size() >= static_cast<size_t>(UINT32_MAX))
	{
		printf("Error adding component to draw list because index is overflow!\n");
		return;
	}

	if (bIsSortByDepthWhenAdded)
	{
		const auto It = std::ranges::lower_bound(AllRenderComponents, component,
			[](const ORenderComponent* componentA, const ORenderComponent* componentB)
			{
				return componentA->GetWorldLocation().Y + componentA->GetDepthKey() < componentB->GetWorldLocation().Y + componentB->GetDepthKey();
			});

		const auto InsertedIt = AllRenderComponents.insert(It, component);
		uint32 CurrentIndex = static_cast<uint32>(std::distance(AllRenderComponents.begin(), InsertedIt));
		
		for (auto i = InsertedIt; i != AllRenderComponents.end(); ++i)
		{
			(*i)->SetRegistryRenderIndex(CurrentIndex);
			CurrentIndex++;
		}
	}
	else
	{
		component->SetRegistryRenderIndex(static_cast<uint32>(AllRenderComponents.size()));
		AllRenderComponents.push_back(component);	
	}
}

void RRenderLayer::RemoveComponent(const ORenderComponent* component)
{
	if (!component)
	{
		printf("Error component is nullptr\n");
		return;
	}
	
	if (component->GetRegistryRenderIndex() >= AllRenderComponents.size() || AllRenderComponents[component->GetRegistryRenderIndex()] != component)
	{
		return; 
	}

	if (bIsSortByDepthWhenAdded)
	{
		const auto It = AllRenderComponents.begin() + component->GetRegistryRenderIndex();
		const auto NextIt = AllRenderComponents.erase(It);
		
		uint32 CurrentIndex = component->GetRegistryRenderIndex();
		for (auto i = NextIt; i != AllRenderComponents.end(); ++i)
		{
			(*i)->SetRegistryRenderIndex(CurrentIndex);
			CurrentIndex++;
		}
	}
	else
	{
		if (const uint32 Last = static_cast<uint32>(AllRenderComponents.size() - 1); component->GetRegistryRenderIndex() != Last)
		{
			AllRenderComponents[component->GetRegistryRenderIndex()] = AllRenderComponents[Last];
			AllRenderComponents[component->GetRegistryRenderIndex()]->SetRegistryRenderIndex(component->GetRegistryRenderIndex());
		}
		AllRenderComponents.pop_back();
	}
}

void RRenderLayer::ClearAll()
{
	for (auto* comp : AllRenderComponents)
	{
		if (comp) 
		{
			comp->SetRegistryRenderIndex(UINT32_MAX);
		}
	}
	AllRenderComponents.clear();
}
