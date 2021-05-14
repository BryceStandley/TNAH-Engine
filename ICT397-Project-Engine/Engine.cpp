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

    gui.Init();


    currentScene = 0;

	for (int i = 1; i <= amount; i++)
	{
	    Scene* scene = new Scene("Scene " + std::to_string(i), render);
        gameScenes.push_back(scene);
		std::string path = "./res/scripts/scene" + std::to_string(i) + ".lua";
		if(Debugger::GetInstance()->debugToConsole) std::cout << "Path: " << path << std::endl;
		LuaScenes(path, i-1);
		scene->FindPlayerIndice();

		//Making sure we set the players position to be above the terrain
		glm::vec3 playerStartPos;
        playerStartPos = scene->GetGameObject(scene->GetPlayerIndice())->GetPos();
        playerStartPos.y = scene->WorldToTerrainPosition(playerStartPos, true).y + 1.5f;
        scene->GetGameObject(scene->GetPlayerIndice())->SetPos(playerStartPos);
		window->UpdateCamera(playerStartPos);
		scene->MoveObjectAwayFromPlayer();
		scene->Load();
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
			//Add scene loading and deloading
			GameTimer::getInstance().UpdateTime(window->GetCurrentTime());
            //Imgui new frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            deltaTime = window->GetTime();


			window->Update();
			ExitScreen e = gameScenes[currentScene]->GetExitScreen();
			e.SetExitScreenDisplay(window->GetDisplay());
			gameScenes[currentScene]->SetExitScreen(e);
			gameScenes[currentScene]->Run(window->GetLens(), deltaTime, false);
			glm::vec3 pos = gameScenes[currentScene]->GetGameObject(gameScenes[currentScene]->GetPlayerIndice())->GetPos();
			window->UpdateCamera(pos);
			window->GameInput(deltaTime);
			window->MouseMove();
			gameScenes[currentScene]->RunPlayer(window->GetLens(), deltaTime, false);

            //build GUI elements
            if(Debugger::GetInstance()->drawDebugPanel)
            {
                gui.DrawDebugUI(window);
            }


            //Render GUI
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			window->Buffer();
		}

		std::cout << "CLOSING::ENGINE_WILL_EXIT" << std::endl;
	}
}

void Engine::LuaScenes(std::string file, int i)
{
	{
		lua_State* L = LuaManager::getInstance().getLuaState();
		getGlobalNamespace(L).beginClass<Scene>("scene").addFunction("MakeGameObject", &Scene::MakeGameObject).endClass().beginClass<GameObject>("GameObject").endClass().deriveClass<Enemy, GameObject>("Enemy")
			//.addProperty("enemyVelocity", &Enemy::enemyVelocity)
			//.addProperty("newPos", &Enemy::newPos)
			//.addProperty("Print", &Enemy::Print)
			//.addFunction("getFSM", &Enemy::getFSM)
			.addFunction("Print", &Enemy::Print)
			.endClass();

			//.beginClass<stateMachine<Enemy>>("EnemyState")
			//.addFunction("GetPrevState", &stateMachine<Enemy>::getPreviousState)
			//.addFunction("GetPrevState", &stateMachine<Enemy>::getCurrentState)
			//.addFunction("GetPrevState", &stateMachine<Enemy>::getGlobalState)
			//.endClass()
			//.beginClass<wander_state>("wander_state")
			//.addStaticFunction("get_wander_state", &wander_state::getInstance)
			//.endClass()
			//.beginClass<alert_state>("alert_state")
			//.addStaticFunction("get_alert_state", &alert_state::getInstance)
			//.endClass()
			//.beginClass<chase_state>("chase_state")
			//.addStaticFunction("get_chase_state", &chase_state::getInstance)
			//.endClass()
			//.beginClass<flee_state>("flee_state")
			//.addStaticFunction("get_flee_state", &flee_state::getInstance)
			//.endClass()
			//.beginClass<attack_state>("attack_state")
			//.addStaticFunction("get_attack_state", &attack_state::getInstance)
			//.endClass()
			//.beginClass<die_state>("die_state")
			//.addStaticFunction("get_die_state", &die_state::getInstance)
			//.endClass()
			//.beginClass<global_state>("global_state")
			//.addStaticFunction("get_global_state", &global_state::getInstance)
			//.endClass();
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