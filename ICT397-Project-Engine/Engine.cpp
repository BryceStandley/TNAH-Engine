#include "Engine.h"

Engine::Engine()
{
	lua_State* L = LuaManager::getInstance().getLuaState();
	int amount = 1;
	int width = 600;
	int height = 800;
	std::string name = "Error loading name";

	if (luaL_dofile(L, "./res/scripts/engine.lua"))
	{
		std::cout << "ENGINE::SCRIPT_ERROR::COULD_NOT_OPEN::LOADING_INITIAL_VALUES" << std::endl;
		amount = 1;
		width = 600;
		height = 800;
		name = "Error loading name";
	}
	else
	{
		std::cout << "ENGINE::SCRIPT_RUNNING" << std::endl;
		LuaRef w = getGlobal(L, "width");
		LuaRef h = getGlobal(L, "height");
		LuaRef n = getGlobal(L, "name");
		LuaRef a = getGlobal(L, "amount");

		if (w.isNumber())
		{
			width = w.cast<int>();
		}

		if (h.isNumber())
		{
			height = h.cast<int>();
		}
		
		if (a.isNumber())
		{
			amount = a.cast<int>();
		}

		if (n.isString())
		{
			name = n.cast<std::string>();
		}
	}

	if (glfwInit())
	{
		window = new GlfwWindow();
		window->Init(name, width, height);
		window->FrameBuffer();
		running = true;
	}
	else
	{
		running = false;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		running = false;
	}
	else
	{
		render = new OpenGL();
		render->DepthTest();
	}

	currentScene = 0;

	for (int i = 1; i <= amount; i++)
	{
	    Scene* scene = new Scene("Scene " + i, render);
        gameScenes.push_back(scene);
		std::string path = "./res/scripts/scene" + std::to_string(i) + ".lua";
		std::cout << "Path: " << path << std::endl;
		LuaScenes(path, i-1);
		scene->FindPlayerIndice();

	}

}

Engine::~Engine()
{
	if (window != nullptr)
		delete[] window;
}

void Engine::Run()
{
	float deltaTime;
	if (!running)
	{
		std::cout << "ERROR::RUNNING_FALSE::ENGINE_WILL_EXIT" << std::endl;
	}
	else
	{
		while (!window->Running())
		{
			deltaTime = window->GetTime();

			window->Update();
			gameScenes[currentScene]->Run(window->GetLens(), deltaTime);
			glm::vec3 pos = gameScenes[currentScene]->GetGameObject(gameScenes[currentScene]->GetPlayerIndice())->GetPos();
			window->UpdateCamera(pos);
			window->GameInput(deltaTime);
			window->MouseMove();

			window->Buffer();
		}

		std::cout << "CLOSING::ENGINE_WILL_EXIT" << std::endl;
	}
}

void Engine::LuaScenes(std::string file, int i)
{
	{
		lua_State* L = LuaManager::getInstance().getLuaState();
		getGlobalNamespace(L).beginClass<Scene>("scene").addFunction("MakeGameObject", &Scene::MakeGameObject).endClass();
		setGlobal(L, gameScenes[i], "cs");
		if (luaL_dofile(L, file.c_str()))
		{
			std::cout << "Scene lua file not found" << std::endl;
		}
		else
		{
			std::cout << "SCENE_" << i + 1 << "::RUNNING" << std::endl;
		}
	}
}