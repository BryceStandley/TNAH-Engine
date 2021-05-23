#pragma once
#include "GUI.h"
#include "Player.h"
#include "MainMenuGUI.h"
class GameGUI : public GUI
{

public:

	GameGUI(std::string scriptPath);

	virtual void Draw(Player* dude);

	bool displayGameUI = true;
	bool displayDeathScreen = false;

	void HideGameUI();
	void DisplayDeathScreen();

	void DisplayGameUI();

private:
	/**
	 * \brief style of the game UI
	 */
	std::string style;

	/**
	 * @brief Reference to the game window for GUI events
	 */
	GlfwWindow* w;

	/**
	 * @brief Reference to the main menu GUI object
	 */
	MainMenuGUI* mainMenuGui;
};

