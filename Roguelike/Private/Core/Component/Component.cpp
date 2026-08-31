// Copyright deRenevo. All rights reserved.

#include <Core/Component/Component.h>

OComponent::OComponent(std::string name) : OObject(name)
{
}

OComponent::OComponent() : OObject()
{
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

void OComponent::SetOwner(AActor* owner)
{
	Owner = owner;
}

void OComponent::SetIsActive(bool isActive)
{
	bIsActive = isActive;
}

AActor* OComponent::GetOwner() const
{
	return Owner;
}

bool OComponent::IsActive() const
{
	return bIsActive;
}
