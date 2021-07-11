#include <TNAH.h>
#include "Scene.h"

class Game : public tnah::Application
{
public:
	Game()
	{
		lua_State* L = LuaManager::getInstance().getLuaState();

		getGlobalNamespace(L)
			.beginClass<game::Scene>("scene")
			.addFunction("MakeGameObject", &tnah::Scene::MakeGameObject)
			.endClass();
	}


	~Game()
	{
	}

	void Run();

};

void Game::Run()
{
	Engine* e = new Engine();

	game::Scene* scene = new game::Scene("World", e->GetRenderer());
	e->gameScenes.push_back(scene);
	e->gameScenes[0]->SetGameWindow((tnah::GlfwWindow*)e->GetWindow());


	e->Run();
}


tnah::Application* tnah::CreateApplication()
{
	return new Game();
}
