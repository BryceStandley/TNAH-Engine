#pragma once
#include <string>
#include "GameObjects.h"
#include "GameAssetFactory.h"
#include "Terrain.h"
#include "Shader.h"
#include "TextureLoader.h"
#include "camera.h"
#include "Skybox.h"
#include "OpenGL.h"
#include "Debugging.h"
#include "ExitScreen.h"

/**
* @class Scene
* @brief Contains the aspects of a game that would be held in a scene, this
* being gameObjects, Terrain, Skybox
* 
* Designed so many scenes can be made and run throught the game, allowing for a terrain and skybox, and
* many different gameobjects
*
* @author Christoper Logan
* @version 01
* @date 29/03/2021 Christopher Logan, Started
*
*@author Bryce Standley
*@version 02
*@date 06/04/2021 Bryce Standley, Ammended
*
*
**/
class Scene
{
public:
		/**
		* @brief Default constructor
		*/
	Scene() {}
		/**
		* @brief Name and Renderer constructor
		* @param The name of the scene
		* @param The renderer pointer
		*/
	Scene(std::string name, Renderer * render);

		/**
		* @brief Destructor
		*/
	~Scene();

		/**
		* @brief Runs the scene, setting up objects for rendering and changes
		* @param lens - Holds information to do with the position of the camera, projects and views
		*/
	void Run(View lens, float time, bool exit);

		/**
		* @brief Initilises the scene, setting up the terrain and skybox
		*/
	void Init();

		/**
		* @brief Gets the name of the current scene
		* @return string
		*/
	std::string GetSceneName() const { return sceneName; }

		/**
		* @brief Function that uses the game asset factory to create a new game object
		* @param t - the type of game object it is
		* @param n - Name of the object
		* @param modalName - the file path to load in the model
		* @param shaderV - The vertex shader file path
		* @param shaderF - The fragment shader file path
		* @param scale - The scale of the object
		* @param x - The x positon of the object
		* @param y - The y position of the object
		* @param z - The z position of the object
		* @param rotate - Sets if the model needs to be rotated on entry
		* @param speed - The speed at which it moves
		*/
	void MakeGameObject(std::string t, std::string script, float scale, float x, float y, float z);

		/**
		* @brief Gets a gameobject from the game objects
		* @param i - The indice of the game object
		*/
	GameObject *GetGameObject(int i) { return gameObjects[i]; }

		/**
		* @brief Updates the players position in relation to the world
		* @param position - The position of the camera
		*/
	void UpdatePlayer(glm::vec3 position, glm::vec3 rotation);

		/**
		* @brief Gets the playerInd value and returns it
		*/
	int GetPlayerIndice() { return playerInd; }

	/**
	 * @brief Finds the playerInd value within the Scenes gameObjects
	 */
	void FindPlayerIndice();

	/**
	 * @brief Checks the players position against scene game objects for collisions
	 * @param pos - current position the player has moved to
	 * @return vec3 - new position if player collides with a object
	 */
	glm::vec3 CheckSceneCollision(glm::vec3 pos);

	/**
	 *
	 * @param o
	 * @param d
	 * @param so
	 * @param radius
	 * @param ip
	 * @return bool
	 */
	static bool intersectRaySegmentSphere(glm::vec3 o, glm::vec3 d, glm::vec3 so, float radius, glm::vec3 &ip);

	/**
	 * @brief Returns the scenes terrain data
	 * @return terrain
	 */
	Terrain* GetSceneTerrain(){return gameTerrain;}

	/**
	 * @brief Converts a given world vec3 to terrain position for height/Y calculations
	 * @return vec3 - position relative to the terrain
	 */
	glm::vec3 WorldToTerrainPosition(glm::vec3 p, bool average);

	ExitScreen GetExitScreen(){return exitScreen;}

	void SetExitScreen(ExitScreen screen) { exitScreen = screen; }

	/**
	 * @brief moves all objects away from the player if they spawn to close to the player
	 */
    void MoveObjectAwayFromPlayer();

	void RunPlayer(View lens, float time, bool exit)
	{
		if(!exitScreen.exitScreenDisplay)
			gameObjects[playerInd]->Render(lens, time, gameRenderer);
	}

	void UpdateGameObject(glm::vec3 position, int i);

private:
		///The game renderer that renders items
	Renderer* gameRenderer;

		///The scenes name
	std::string sceneName;

		///The game asset factory that creates the different game objects for the scene
	GameAssetFactory * factory;

		///The vector that holds each game object
	std::vector<GameObject*> gameObjects;

		///The games terrain
	Terrain *gameTerrain;

		///The games skybox
	Skybox* gameSkybox;

		///The texture loader for the game
	TextureLoader textureLoader;

		///The viewpoints of the camera and projections
	View lens;

		///The indice of the player game object
	int playerInd;

		///Debugger
	tnah::Debugging debugger;

		///The exit screen
	ExitScreen exitScreen;

		///If the exit screen is displayed
	bool exitScreenDisplay = false;
};

