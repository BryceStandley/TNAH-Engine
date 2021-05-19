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
}

void GameGUI::Draw(Player* dude)
{
	bool open = true;
	bool* open_ptr = &open;

	ImVec2 windowSize = ImGui::GetIO().DisplaySize;
	ImVec2 windowPos;
	windowPos.x = 0;

	ImGuiWindowFlags window_flags = 0;

	if (style == "transparent")
	{
		// set transparent bg
		
		window_flags |= ImGuiWindowFlags_NoBackground;
		window_flags |= ImGuiWindowFlags_NoTitleBar;
	}


	std::string windowName = "GameUI";
	//Set window size and position before creating the window context from imgui
	ImGui::SetNextWindowSize(ImVec2(0, 0));
	ImGui::SetNextWindowPos(ImVec2(windowPos.x, 0), true);
	ImGui::Begin(windowName.c_str(), open_ptr,  window_flags); //Create the window
	//Set scale for the font only for the game ui
	ImGui::SetWindowFontScale(2.0f);
	ImGui::Text("Points: %d     Tokens: %d      Current Token: %s      Kill Count: %d      Health: %d", dude->getPoints(),dude->getTokensCollected(), singleton<Manager>::getInstance().prevToken.c_str(), dude->getKills(), dude->getHealth());

	ImGui::End();
}
