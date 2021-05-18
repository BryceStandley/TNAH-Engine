#pragma once
#include "GUI.h"

class DebugGUI : public GUI
{
public: 

	DebugGUI(std::string scriptPath);

	virtual void Draw();


private:
	bool fps, console, collisions, weapons, animations, md2, token, fsm;
};

