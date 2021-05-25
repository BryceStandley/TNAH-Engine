#pragma once
#include "GUI.h"

/**
 * @brief Main GUI init
 * @file MainGUI.h
 * @author Bryce Standley
 * @date MAY 2021
 */

class MenuGUI : public GUI
{

	/**
	 * @brief Init function used to init the ImGui modules
	 */
	virtual void Init();

	/**
	 * @brief Draw function to draw GUI to the screen
	 */
	virtual void Draw();



};

