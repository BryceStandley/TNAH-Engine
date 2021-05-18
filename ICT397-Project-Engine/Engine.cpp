#include "Engine.h"

Engine::Engine()
{
	lua_State* L = LuaManager::getInstance().getLuaState();

	getGlobalNamespace(L)
		.beginClass<Scene>("scene")
			.addFunction("MakeGameObject", &Scene::MakeGameObject)
		.endClass()
		.beginClass<glm::vec3>("vec3")
		.endClass()
		.beginClass<GameObject>("GameObject")
			.addFunction("FS", &GameObject::GetScale)
		.endClass()
		.deriveClass<Enemy, GameObject>("Enemy")
			.addData("enemyVelocity", &Enemy::enemyVelocity)
			.addData("newPos", &Enemy::newPos)
			.addFunction("getFSM", &Enemy::getFSM)
			.addFunction("SetState", &Enemy::SetState)
			.addFunction("Print", &Enemy::Print)
			.addFunction("GetDeltaTime", &Enemy::GetDeltaTime)
			.addFunction("getToken", &Enemy::getToken)
			.addFunction("CheckPrevState", &Enemy::CheckPrevState)
			.addFunction("incrementCheck", &Enemy::incrementCheck)
			.addFunction("getCheck", &Enemy::getCheck)
			.addFunction("setToken", &Enemy::setToken)
			.addFunction("setGlobalFlag", &Enemy::setGlobalFlag)
			.addFunction("ChangeState", &Enemy::ChangeState)
			.addFunction("LookDirection", &Enemy::LookDirection)
			.addFunction("setWander", &Enemy::setWander)
			.addFunction("Distance", &Enemy::Distance)
			.addFunction("GetPos", &Enemy::GetPos)
			.addFunction("SetPos", &Enemy::SetPos)
			.addFunction("setDirection", &Enemy::setDirection)
			.addFunction("wander", &Enemy::wander)
			.addFunction("SetMoving", &Enemy::SetMoving)
			.addFunction("GetMoving", &Enemy::GetMoving)
			.addFunction("getEnemyVelocity", &Enemy::getEnemyVelocity)
			.addFunction("getVelocity", &Enemy::getVelocity)
			.addFunction("getNewPos", &Enemy::getNewPos)
			.addFunction("moveTo", &Enemy::moveTo)
			.addFunction("setEnemyVelocity", &Enemy::setEnemyVelocity)
			.addFunction("setNewPos", &Enemy::setNewPos)
			.addFunction("SendMessage", &Enemy::SendMessage)
			.addFunction("getTimer", &Enemy::getTimer)
			.addFunction("setTimer", &Enemy::setTimer)
			.addFunction("incrementTimer", &Enemy::incrementTimer)
			.addFunction("pursue", &Enemy::pursue)
			.addFunction("getCamPos", &Enemy::getCamPos)
			.addFunction("evade", &Enemy::evade)
			.addFunction("getDeathAnim", &Enemy::getDeathAnim)
			.addFunction("setDeathAnim", &Enemy::setDeathAnim)
			.addFunction("SetKillFSM", &Enemy::SetKillFSM)
			.addFunction("isAlive", &Enemy::isAlive)
			.addFunction("getGlobalFlag", &Enemy::getGlobalFlag)
		.endClass();


	int amount = 1;
	int width = 600;
	int height = 800;
	bool debugMode = false;
	std::string name = "Error loading name";

	if (luaL_dofile(L, "./res/scripts/engine.lua"))
	{
		std::cout << "ENGINE::SCRIPT_ERROR::COULD_NOT_OPEN::LOADING_INITIAL_VALUES" << std::endl;
		amount = 1;
		width = 600;
		height = 800;
		name = "Error loading name";
		debugMode = false;
	}
	else
	{
		std::cout << "ENGINE::SCRIPT_RUNNING" << std::endl;
		LuaRef w = getGlobal(L, "width");
		LuaRef h = getGlobal(L, "height");
		LuaRef n = getGlobal(L, "name");
		LuaRef a = getGlobal(L, "amount");
		LuaRef d = getGlobal(L, "debugMode");

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

		if (d.isBool()) { debugMode = d.cast<bool>(); }
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

	//Init ImGui Only needs to be done once
	GUI gui;
	gui.Init((GlfwWindow*)window);

	//Init the debug gui if its enabled
	if (debugMode) { debugGui = new DebugGUI("./res/scripts/menus/debug.lua"); }


    currentScene = 0;
	Scene* scene = new Scene("World", render);
    gameScenes.push_back(scene);
	std::string path = "./res/scripts/scene.lua";
	if(Debugger::GetInstance()->debugToConsole) std::cout << "Path: " << path << std::endl;
	
	LoadScene(path);
	MainMenuGUI::GetInstance()->DisplayMainMenu();
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

            if(MainMenuGUI::GetInstance()->loadGameClicked)
            {
                gameScenes[0]->LoadSaveFile();
                MainMenuGUI::GetInstance()->loadGameClicked = false;
            }



                ExitScreen e = gameScenes[currentScene]->GetExitScreen();
                e.SetExitScreenDisplay(window->GetDisplay());
                gameScenes[currentScene]->SetExitScreen(e);

                Weapon w = gameScenes[currentScene]->GetPlayerWeapon();
                w.firingWeapon = window->GetWeaponFire();
                gameScenes[currentScene]->SetPlayerWeapon(w);


                gameScenes[currentScene]->Run(window->GetLens(), deltaTime, false);
                glm::vec3 pos = gameScenes[currentScene]->GetGameObject(gameScenes[currentScene]->GetPlayerIndice())->GetPos();
                window->UpdateCamera(pos);
                window->GameInput(deltaTime);
                window->MouseMove();
            if(!MainMenuGUI::GetInstance()->displayingAMenu)
            {
                gameScenes[currentScene]->RunPlayer(window->GetLens(), deltaTime, false);

                //build GUI elements
                if(debugGui && Debugger::GetInstance()->drawDebugPanel)
                {
                    debugGui->Draw();
                }
            }

            //Render GUI
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			window->Buffer();

            if(MainMenuGUI::GetInstance()->saveGameClicked)
            {

                MainMenuGUI::GetInstance()->saveGameClicked = false;
            }

		}
		//todo: Add a auto save option in settings manager and use it to trigger save
        gameScenes[0]->SaveGame();
		std::cout << "CLOSING::ENGINE_WILL_EXIT" << std::endl;
	}
}

void Engine::LoadScene(std::string file)
{
	gameScenes[0]->Load(file);
	glm::vec3 playerStartPos;
	playerStartPos = gameScenes[0]->GetGameObject(gameScenes[0]->GetPlayerIndice())->GetPos();
	playerStartPos.y = gameScenes[0]->WorldToTerrainPosition(playerStartPos, true).y + 1.5f;
	gameScenes[0]->GetGameObject(gameScenes[0]->GetPlayerIndice())->SetPos(playerStartPos);
	window->UpdateCamera(playerStartPos);
	gameScenes[0]->MoveObjectAwayFromPlayer();
}