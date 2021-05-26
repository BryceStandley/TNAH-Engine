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

	float terrainHeight;

	/**
	 * @brief Remaps a value from one range to another
	 * @param value - value to remap
	 * @param oldMin - old min value
	 * @param oldMax - old max value
	 * @param newMin  - new min value
	 * @param newMax - new max value
	 * @return output - new value in the same range of the old values but within the new values
	 */
	float Remap(float value, float oldMin, float oldMax, float newMin, float newMax);

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

