// Copyright deRenevo. All rights reserved.

#include <Core/Scene/Scene.h>
#include <iostream>

void Scene::OnEnter()
{
    PreSceneConstruction();;
    SceneConstruction();
    PostSceneConstruction();
}

void Scene::OnExit()
{
    Destroy();
}

void Scene::DoTick(float DeltaTime)
{
    if (!GetIsPendingKill()) return; // if sttarting process deleting object thet stop Function 
    Tick(DeltaTime);
}

void Scene::DoDraw()
{
    if (!GetIsPendingKill()) return; // if sttarting process deleting object thet stop Function 
    Draw();
}


void Scene::Tick(float DeltaTime)
{
}

void Scene::Draw()
{
}

void Scene::SceneConstruction()
{
    
}

void Scene::PreSceneConstruction()
{
	
}

void Scene::PostSceneConstruction()
{
	
}

void Scene::Destroy()
{
    SetIsPendingKill();
}
