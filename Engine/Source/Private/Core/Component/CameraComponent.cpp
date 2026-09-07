// Copyright deRenevo. All rights reserved.

#include "Core/Component/CameraComponent.h"
#include "Core/Scene/SceneManager.h"
#include  "Core/Scene/Scene.h"

OCameraComponent::OCameraComponent() : OCameraComponent("CameraComponent")
{

}

OCameraComponent::OCameraComponent(const std::string& name) : OSceneComponent(name)
{
	Offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
}