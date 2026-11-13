// Copyright deRenevo. All rights reserved.

#include "Core/Component/Component.h"

OComponent::OComponent() : OComponent(nullptr, "Component")
{

}

OComponent::OComponent(const std::string& name) : OComponent(nullptr, name)
{

}

OComponent::OComponent(AActor* owner) : OComponent(owner, "Component")
{

}

OComponent::OComponent(AActor* owner, const std::string& name) : OObject(name)
{
	OComponent::SetOwner(owner);
}

void OComponent::DoTick(float deltaTime)
{
	if (GetIsPendingKill() || !bIsActive) return;
	Tick(deltaTime);
}

void OComponent::BeginPlay()
{
	if (bIsHasBeginPlay) return;
	bIsHasBeginPlay = true;
}

void OComponent::EndPlay()
{
	if (!bIsHasBeginPlay) return;
}

void OComponent::OnAttach()
{

}

void OComponent::OnDetach()
{
}

void OComponent::Tick(const float deltaTime)
{
}
