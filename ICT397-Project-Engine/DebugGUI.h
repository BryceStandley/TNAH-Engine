#pragma once
#include "GUI.h"
#include <string>

class DebugGUI : public GUI
{
public: 

	DebugGUI(std::string scriptPath);

	/**
	 * @brief Init for the debug ui menu
	 * 
	 * \param win
	 */
	void Init(GlfwWindow* win);

	virtual void Draw();


private:
	GlfwWindow* w;
	bool fps, console, collisions, weapons, animations, md2, token, fsm;
};

