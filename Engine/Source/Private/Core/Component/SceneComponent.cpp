// Copyright deRenevo. All rights reserved.

#include "Core/Component/SceneComponent.h"
#include "Core/Actor/Actor.h"

#include <algorithm>
#include <print>
#include <raylib.h>

OSceneComponent::OSceneComponent() : OSceneComponent(nullptr, {0, 0}, "SceneComponent")
{

}

OSceneComponent::OSceneComponent(const std::string& name) : OSceneComponent(nullptr, {0, 0}, name)
{

}

OSceneComponent::OSceneComponent(AActor* owner) : OSceneComponent(owner, {0, 0}, "SceneComponent")
{
}

OSceneComponent::OSceneComponent(AActor* owner, const Vector2& location) : OSceneComponent(owner, location, "SceneComponent")
{
}

OSceneComponent::OSceneComponent(const Vector2& location, const std::string& name) : OSceneComponent(nullptr, location, name)
{

}

OSceneComponent::OSceneComponent(AActor* owner, const Vector2& location, const std::string& name) : OComponent(owner, name), Location(location)
{

}

OSceneComponent::~OSceneComponent()
{

}

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
