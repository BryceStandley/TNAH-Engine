#pragma once
#include "GUI.h"
#include "PhysicsManager.h"
using namespace tnah;

class TNAH_API DebugGUI : public GUI
{
public: 

	/*
	 * @brief Constructor of the debug ui
	 */
	DebugGUI(std::string scriptPath);

	/**
	 * @brief Override of default GUI draw function to draw ImGui to the screen
	 */
	virtual void Draw();


private:
	/**
	 * @brief local bools for toggleing with lua
	 */
	bool console, collisions, weapons, animations, md2, token, fsm, noClip;
	/**
	 * @brief local string for toggleing with lua
	 */
	std::string logFilePath;
	/**
	 * @brief local int for toggleing with lua
	 */
	int logType;

	tnah::Debugger* debugger;

};

