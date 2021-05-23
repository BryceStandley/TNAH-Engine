#include "GameGUI.h"

GameGUI::GameGUI(std::string scriptPath)
{
	lua_State* L = LuaManager::getInstance().getLuaState();

	if (!luaL_dofile(L, scriptPath.c_str()))
	{
		luabridge::LuaRef s = luabridge::getGlobal(L, "style");

		if (s.isString()) style = s.cast<std::string>();

	}
	else
	{
		style = "transparent"; //transparent, dark or light;
	}

	mainMenuGui = MainMenuGUI::GetInstance();
}
void GameGUI::HideGameUI()
{
	displayGameUI = false;
	displayDeathScreen = false;
}
void GameGUI::DisplayDeathScreen()
{
	displayDeathScreen = true;
	displayGameUI = false;
	MainMenuGUI::GetInstance()->DisplayDeathScreen();
}

void GameGUI::DisplayGameUI()
{
	displayDeathScreen = false;
	displayGameUI = true;
	MainMenuGUI::GetInstance()->HideMenus();
}


void GameGUI::Draw(Player* dude)
{
	bool open = true;
	bool* open_ptr = &open;

	ImVec2 windowSize = ImGui::GetIO().DisplaySize;
	ImVec2 windowPos;
	windowPos.x = 0;

	ImVec2 centerPos = ImVec2(0, 20.0f);
	centerPos.x = (windowSize.x / 3.0f);

	ImGuiWindowFlags window_flags = 0;

	if (style == "transparent")
	{
		// set transparent bg
		
		window_flags |= ImGuiWindowFlags_NoBackground;
		window_flags |= ImGuiWindowFlags_NoTitleBar;
	}



	if(displayGameUI)
	{
		std::string currentToken;
		if(singleton<Manager>::getInstance().timer <= 0)
		{
			currentToken = "None";
		}
		else
		{
			currentToken = singleton<Manager>::getInstance().prevToken;
		}

		std::string windowName = "GameUI";
		//Set window size and position before creating the window context from imgui
		ImGui::SetNextWindowSize(ImVec2(0, 0));
		ImGui::SetNextWindowPos(ImVec2(windowPos.x, 0), true);
		ImGui::Begin(windowName.c_str(), open_ptr,  window_flags); //Create the window
		ImGui::SetWindowFontScale(2.0f);
		ImGui::Text("Points: %d     Tokens: %d      Current Token: %s      Kill Count: %d      Health: %d",
		            dude->getPoints(), dude->getTokensCollected(), currentToken.c_str(),
		            dude->getKills(), dude->getHealth());
		if(Debugger::GetInstance()->debugPlayerPos)
		{
			ImGui::SetWindowFontScale(1.0f);
			ImGui::Text("Current Player Position: %s", Debugger::GetInstance()->DebugVec3(dude->GetPos()).c_str());

		}
		if(Debugger::GetInstance()->stickyFPSCounter)
		{
			ImGui::SetWindowFontScale(1.0f);
			ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
		}
	}
	else if(displayDeathScreen)
	{
		window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoTitleBar;
		std::string windowName = "bg";
		ImGui::SetNextWindowSize(windowSize); // fill the whole application window
		ImGui::SetNextWindowPos(ImVec2(0,0), true); // set to draw from the top left corner
		ImGui::Begin(windowName.c_str(), open_ptr,  window_flags); //Create the window
		ImGui::End();

		window_flags |= ImGuiWindowFlags_NoBackground;
		windowName = "DeathUI";
		ImGui::SetNextWindowSize(windowSize); // fill the whole application window
		ImGui::SetNextWindowPos(ImVec2(windowSize.x / 3.0f , (windowSize.y / 5.0f)), true); // set to draw from the top left corner
		ImGui::Begin(windowName.c_str(), open_ptr, window_flags); //Create the window


		// display death text texture
		ImGui::Text("Points: %d", dude->getPoints());
		ImGui::Text("Tokens: %d", dude->getTokensCollected());
		ImGui::Text("Kill Count: %d", dude->getKills());

		if(ImGui::Button("PLAY AGAIN", centerPos))
		{
			//reset the player and stats
			dude->Reset();
			DisplayGameUI();
		}
		if(ImGui::Button("QUIT", centerPos))
		{
			mainMenuGui->endScreenButtonClicked = true;
		}
	}
	ImGui::End();
}
