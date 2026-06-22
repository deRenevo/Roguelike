#pragma once

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	void OnEnter(); // -> Loading resources
	virtual void OnExit(); // -> Cleaning up resources
	virtual void Tick(float DeltaTime); //-> every frame is processed
	virtual void Draw();
	virtual void KeyPressEvent(int key);

protected:
	virtual void SceneConstruction(); //-> processed when changing priced
	virtual void PreSceneConstruction(); //-> processed before SceneConstruction
	virtual void PostSceneConstruction(); //-> processed after SceneConstruction
};