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
			.addFunction("getDifficulty", &Enemy::getDifficulty)
			.addFunction("setHealth", &Enemy::setHealth)
			.addFunction("SetAccuracy", &Enemy::SetAccuracy)
			.addFunction("SetDamage", &Enemy::SetDamage)
			.endClass()
			.deriveClass<Player, GameObject>("Player")
			.addFunction("GetToken", &Player::GetToken)
			.addFunction("SetToken", &Player::SetToken)
			.addFunction("incrementTokensCollected", &Player::incrementTokensCollected)
			.addFunction("increasePoints", &Player::increasePoints)
			.addFunction("setDamage", &Player::setDamage)
			.addFunction("getDamage", &Player::getDamage)
			.addFunction("SetPrevInstanceToken", &Player::SetPrevInstanceToken)
			.addFunction("SetInstanceToken", &Player::SetInstanceToken)
			.addFunction("GetPrevInstanceToken", &Player::GetPrevInstanceToken)
			.addFunction("GetInstanceToken", &Player::GetInstanceToken)
			.addFunction("GetInstanceTimer", &Player::GetInstanceTimer)
			.addFunction("ChangeState", &Player::ChangeState)
			.addFunction("setMultiplier", &Player::setMultiplier)
			.addFunction("SetInstanceSpeed", &Player::SetInstanceSpeed)
			.addFunction("getHealth", &Player::getHealth)
			.addFunction("setHealth", &Player::setHealth)
			.endClass();


		int amount = 1;
		int width = 600;
		int height = 800;
		bool debugMode = false;
		std::string name = "Error loading name";
		if (luaL_dofile(L, "res/scripts/engine.lua"))
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
		Debugger::GetInstance()->OpenLogger();
		mainMenuGui = MainMenuGUI::GetInstance();

		currentScene = 0;
		Scene* scene = new Scene("World", render);
		gameScenes.push_back(scene);

		gameScenes[currentScene]->SetGameWindow((GlfwWindow*)window);

		mainMenuGui->DisplayMainMenu();
		mainMenuGui->previousMenu = MainMenuGUI::MainMenu;

		render->SetUpReactDebugger(PhysicsManager::GetInstance()->GetDebugRenderer());

	}

	Engine::~Engine()
	{
		if (window != nullptr) { delete[] window; }
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
				//checked every frame in case the user change's the settings
				SettingsManager::GetInstance()->ToggleFullscreen();

				//Add scene loading and deloading
				GameTimer::getInstance().UpdateTime(window->GetCurrentTime());
				//Imgui new frame
				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				deltaTime = window->GetTime();
				window->Update();
				PhysicsManager::GetInstance()->Update(PhysicsManager::GetInstance()->physicsUpdateTimeStep);
				render->UpdateReactDebugVBO();

				if (mainMenuGui->newGameClicked)
				{
					if (!gameScenes[0]->loaded)
					{
						std::string path = "./res/scripts/scene.lua";
						LoadScene(path);
						mainMenuGui->newGameClicked = false;
						mainMenuGui->HideMenus();
					}
					else if (mainMenuGui->playAgainClicked)
					{
						window->UpdateCamera(glm::vec3((52.0f * 12) / 2, 4.0f, (52.0f * 12) / 2));

						gameScenes.clear();
						currentScene = 0;
						Scene* scene = new Scene("World", render);
						gameScenes.push_back(scene);

						std::string path = "./res/scripts/scene.lua";
						LoadScene(path);
						mainMenuGui->newGameClicked = false;
						mainMenuGui->playAgainClicked = false;
						mainMenuGui->mainMenuClosed = false;
						mainMenuGui->HideMenus();
					}
				}

				if (mainMenuGui->loadGameClicked)
				{
					if (gameScenes[0]->LoadSaveFile())
					{
						mainMenuGui->loadGameClicked = false;
						mainMenuGui->HideMenus();
					}
					else
					{
						mainMenuGui->noSaveFileFound = true;
					}
				}



				//Check if a scene is loaded before trying to render or run the scene per frame
				ExitScreen e = gameScenes[currentScene]->GetExitScreen();
				e.SetExitScreenDisplay(window->GetDisplay());
				if (mainMenuGui->endScreenButtonClicked) e.exitScreenDisplay = mainMenuGui->endScreenButtonClicked;
				gameScenes[currentScene]->SetExitScreen(e);

				Weapon w = gameScenes[currentScene]->GetPlayerWeapon();
				w.firingWeapon = window->GetWeaponFire();
				gameScenes[currentScene]->SetPlayerWeapon(w);


				gameScenes[currentScene]->Run(window->GetLens(), deltaTime, false);
				if (gameScenes[currentScene]->loaded)
				{
					glm::vec3 pos = gameScenes[currentScene]->GetGameObject(
						gameScenes[currentScene]->GetPlayerIndice())->GetPos();
					window->UpdateCamera(pos);
				}
				window->GameInput(deltaTime);
				window->MouseMove();

				if (!mainMenuGui->displayingAMenu)
				{
					gameScenes[currentScene]->RunPlayer(window->GetLens(), deltaTime, false);
					//build GUI elements
					if (debugGui && Debugger::GetInstance()->drawDebugPanel)
					{
						debugGui->Draw();
					}
				}

				if (mainMenuGui->saveGameClicked)
				{
					gameScenes[0]->SaveGame();
					mainMenuGui->saveGameClicked = false;
				}




				//Render GUI
				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

				window->Buffer();



			}
			if (!mainMenuGui->noSaveFileFound) gameScenes[0]->SaveGame();
			std::cout << "CLOSING::ENGINE_WILL_EXIT" << std::endl;
			Debugger::GetInstance()->CloseLogger();
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

