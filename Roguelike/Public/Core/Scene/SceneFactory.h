#include <memory>

class Scene;


class SceneFactory
{
	SceneFactory() = delete;

public:
	enum class ESceneList //-> All lists scene. Adding  to switch case in function class 
	{
		None,
		Menu
	};
	static std::unique_ptr<Scene> CreateScene(ESceneList SceneId);
};