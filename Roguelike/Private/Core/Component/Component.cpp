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
	SetOwner(owner);
}

void OComponent::DoTick(float DeltaTime)
{
	if (GetIsPendingKill() || !bIsActive) return;
	Tick(DeltaTime);
}

void OComponent::DoDraw()
{
	if (GetIsPendingKill() || !bIsActive) return;
	Draw();
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

void OComponent::Tick(float DeltaTime)
{
}

void OComponent::Draw()
{
}
