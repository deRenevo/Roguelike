// Copyright deRenevo. All rights reserved.

#include "Core/Actor/PlayerStart.h"

#include "Core/Manager/SceneManager.h"
#include "Core/Scene/Scene.h"

APlayerStart::APlayerStart() : APlayerStart(FVector2D::ZeroVector, "PlayerStart")
{
}

APlayerStart::APlayerStart(const FVector2D worldLocation) : APlayerStart(worldLocation, "PlayerStart")
{
}

APlayerStart::APlayerStart(const FVector2D worldLocation, const std::string& name) : AActor(worldLocation, name), WorldLocation(worldLocation)
{
}

void APlayerStart::BeginPlay()
{
	SceneManager::GetInstance().GetScene()->SetPlayerStart(this);
}
