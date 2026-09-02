// Copyright deRenevo. All rights reserved.

#include "Core/Component/SceneComponent.h"

#include <algorithm>
#include <raylib.h>

#include "Core/Actor/Actor.h"

void OSceneComponent::Draw()
{
	OComponent::Draw();
	for (const std::unique_ptr<OComponent>& Child : Children)
	{
		Child->DoDraw();
	}
}

void OSceneComponent::Tick(float DeltaTime)
{
	OComponent::Tick(DeltaTime);
	for (const std::unique_ptr<OComponent>& Child : Children)
	{
		Child->DoTick(DeltaTime);
	}
}

void OSceneComponent::EndPlay()
{
	OComponent::EndPlay();

	for (std::unique_ptr<OComponent>& Child : Children)
	{
		Child->EndPlay();
	}
}

OSceneComponent::OSceneComponent(const std::string& name) : OComponent(name)
{

}

OSceneComponent::OSceneComponent() : OComponent()
{

}

OSceneComponent::~OSceneComponent()
{

}

void OSceneComponent::SetLocation(const Vector2& location)
{
	Location = location;
}

void OSceneComponent::AddChild(std::unique_ptr<OComponent> child)
{
	if (!child)
	{
		return;
	}
	
	if (GetOwner())
	{
		child->SetOwner(GetOwner());
	}
	
	if (auto* Child = dynamic_cast<OSceneComponent*>(child.get()))
	{
		Child->SetParent(this);
	}

	Children.push_back(std::move(child));
}

void OSceneComponent::RemoveChild(OComponent* child)
{
	if (!child) return;

	auto It = std::ranges::find_if(Children,
		[child](const std::unique_ptr<OComponent>& ptr)
		{
			return ptr.get() == child;
		});

	if (It != Children.end())
	{
		(*It)->EndPlay();
		Children.erase(It);
	}
}

void OSceneComponent::SetParent(OSceneComponent* parent)
{
	Parent = parent;
}

Vector2 OSceneComponent::GetLocation() const
{
	return Location;
}

Vector2 OSceneComponent::GetWorldLocation() const
{
	if (Parent)
	{
		const Vector2 ParentLocation = Parent->GetWorldLocation();
		return {ParentLocation.x + Location.x, ParentLocation.y + Location.y};
	}

	return Location;
}

OSceneComponent* OSceneComponent::GetParent() const
{
	return Parent;
}
