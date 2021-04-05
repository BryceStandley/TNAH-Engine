#pragma once
#include <glad/glad.h>
#include "Windows.h"
#include "Scene.h"
#include "OpenGL.h"
#include <vector>
/**
* @class Engine
* @brief The hub of the entire engine, this class initialises every other
* aspect of the game engine, and also prodvides the gameplay loop.
* It also checks and sets the windower and renderer used throughout the system,
* and provides scene managment
*
* @author Christoper Logan
* @version 01
* @date 15/03/2021 Christopher Logan, Started
* 
* @author Christoper Logan
* @version 02
* @date 5/04/2021 Christopher Logan, Started
*
**/
class Engine
{
public:
	Engine();
	~Engine();
	void Run();
private:

	void InitiliseScene();

		///Pointer for the window
	Window* window;
		///Holds the different scenes
	std::vector<Scene> gameScenes;

		///Pointer for the renderer
	Renderer * render;

		///The current Scene
	int currentScene;
	int totalScenes;

		///The running state of the game
	bool running;
};

