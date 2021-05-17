#pragma once
#include <glad/glad.h>
#include "Windows.h"
#include "Scene.h"
#include "OpenGL.h"
#include <vector>
#include "GUI.h"
#include "Debugger.h"

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
using namespace luabridge;
class Engine
{
public:
		/**
		* @brief Default constructor
		*/
	Engine();

		/**
		* @brief Destructor
		*/
	~Engine();

		/**
		* @brief Runs the game loop
		*/
	void Run();

private:

		/**
		* @brief Loads in a lua scene file, loading up all the assets
		* @param file - The file path to the script
		* @param i - The scene number
		*/
	void LoadScene(std::string file);

		///Pointer for the window
	Window* window;
		///Holds the different scenes
	std::vector<Scene*> gameScenes;

		///Pointer for the renderer
	Renderer * render;

		///The current Scene
	int currentScene;

		///The running state of the game
	bool running;

    /**
     * @brief GUI object used to access gui functions
     */
    GUI gui;
};

