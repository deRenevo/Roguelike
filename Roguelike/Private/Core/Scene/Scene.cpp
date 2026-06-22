#include <Core/Scene/Scene.h>

void Scene::OnEnter()
{
	PreSceneConstruction();
	SceneConstruction();
	PostSceneConstruction();
}

void Scene::OnExit()
{
}

void Scene::Tick(float DeltaTime)
{
}

void Scene::Draw()
{
}

void Scene::KeyPressEvent(int key)
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
