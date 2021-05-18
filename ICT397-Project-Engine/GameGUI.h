#pragma once
#include "GUI.h"
#include "Player.h"
class GameGUI : public GUI
{

public:

	GameGUI(std::string scriptPath);

	virtual void Draw(Player* dude);

private:
	/**
	 * \brief style of the game UI
	 */
	std::string style;

	/**
	 * @brief Reference to the game window for GUI events
	 */
	GlfwWindow* w;
};

