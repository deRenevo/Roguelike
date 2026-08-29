// Copyright deRenevo. All rights reserved.

#include <Core/Actor/PlayerStart.h>
#include <Core/Scene/SceneManager.h>
#include <Core/Scene/Scene.h>

APlayerStart::APlayerStart() : AActor()
{
}

APlayerStart::APlayerStart(Vector2 worldLocation, std::string name) : AActor(worldLocation, name)
{
}

APlayerStart::APlayerStart(Vector2 worldLocation) : AActor(worldLocation)
{
}

void APlayerStart::BeginPlay()
{
    SceneManager::GetInstance().GetScene()->SetPlayerStart(this);
}
