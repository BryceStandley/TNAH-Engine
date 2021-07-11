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
#include "Debugger.h"
#include "ExitScreen.h"
#include "Weapon.h"
#include "GameGUI.h"
#include "EndScreenGUI.h"
#include "MainMenuGUI.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "PhysicsManager.h"
#include "GlfwWindow.h"

////////////////////////////////////////////////////////
////HUGE DISCLAIMER, THIS CLASS IS OUR VERSION OF THE WORLD CLASS WANTED FOR THE ASSIGNEMNT/////
///////////////////////////////////////////////////////

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

namespace tnah {
	class TNAH_API Scene
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
		Scene(std::string name, Renderer* render);

		/**
		* @brief Destructor
		*/
		~Scene();

		/**
		* @brief Runs the scene, setting up objects for rendering and changes
		* @param lens - Holds information to do with the position of the camera, projects and views
		*/
		virtual void Run(View lens, float time, bool exit) {}

		/**
		* @brief Initilises the scene, setting up the terrain and skybox
		*/
		virtual void Init() {}

		/**
		* @brief Loads the scene
		*/
		virtual void Load(std::string file) {}


		/**
		* @brief Saves the save file
		*/
		virtual bool LoadSaveFile() { return false; }


		/**
		* @brief Lerps the positions for terrain walking
		*/
		float Lerp(float a, float b, float t);


		/**
		* @brief Interlopes personions for terrain walking
		*/
		float Interpolate(float a, float b, float blend);


		/**
		* @brief Unloads the scene
		*/
		virtual void Unload() {}

		/**
		* @brief Gets the name of the current scene
		* @return string
		*/
		virtual std::string GetSceneName() const { return sceneName; }

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
		virtual void MakeGameObject(std::string t, std::string script, float scale, float x, float y, float z) {}

		/**
		* @brief Gets a gameobject from the game objects
		* @param i - The indice of the game object
		*/
		virtual GameObject* GetGameObject(int i) { return gameObjects[i]; }

		/**
		* @brief Updates the players position in relation to the world
		* @param position - The position of the camera
		*/
		virtual void UpdatePlayer(glm::vec3 position, glm::vec3 rotation, float time, View lens) {}

		/**
		* @brief Gets the playerInd value and returns it
		*/
		virtual int GetPlayerIndice() { return playerInd; }

		/**
		 * @brief Finds the playerInd value within the Scenes gameObjects
		 */
		virtual int FindPlayerIndice(std::vector<GameObject*> go);

		/**
		 * @brief Checks the players position against scene game objects for collisions
		 * @param pos - current position the player has moved to
		 * @return vec3 - new position if player collides with a object
		 */
		virtual glm::vec3 CheckSceneCollision(glm::vec3 pos) { return glm::vec3(0, 0, 0); }

		/**
		 * @brief Returns the scenes terrain data
		 * @return terrain
		 */
		Terrain* GetSceneTerrain() { return gameTerrain; }

		/**
		 * @brief Converts a given world vec3 to terrain position for height/Y calculations
		 * @return vec3 - position relative to the terrain
		 */
		glm::vec3 WorldToTerrainPosition(glm::vec3 p, bool average);

		/**
		 * @brief Converts the players position into terrain position
		 * @param p - players position
		 * @param terrainPosMovement - How much to check on each axis. p.x + 1 doesnt map to the same as terrainX + 1
		 * @return
		 */
		virtual glm::vec3 PlayerToTerrainPosition(glm::vec3 p, glm::vec3 terrainPosMovement);

		/**
		 * @brief Remaps a value from one range to another
		 * @param value - value to remap
		 * @param oldMin - old min value
		 * @param oldMax - old max value
		 * @param newMin  - new min value
		 * @param newMax - new max value
		 * @return output - new value in the same range of the old values but within the new values
		 */
		virtual float Remap(float value, float oldMin, float oldMax, float newMin, float newMax);

		/**
		 * @brief Uses biliniear interpolation to output a new position
		 * @param p
		 * @return
		 */
		float BilinearInterpolation(glm::vec3 p);

		ExitScreen GetExitScreen() { return exitScreen; }

		void SetExitScreen(ExitScreen screen) { exitScreen = screen; }

		/**
		 * @brief moves all objects away from the player if they spawn to close to the player
		 */
		virtual void MoveObjectAwayFromPlayer() {}

		/**
		* @brief Runs the players information
		*/
		virtual void RunPlayer(View lens, float time, bool exit){}


		/**
		* @brief Updates the players game object
		*/
		virtual void UpdateGameObject(glm::vec3 position, int i, float time) {}


		/**
		* @brief Obstacle avoidance for the enemies
		*/
		virtual glm::vec3 EnemyObstacleAvoidance(GameObject* self, glm::vec3 newPosition) { return glm::vec3(0, 0, 0); }


		/**
		* @brief Shoots the gun
		*/
		virtual void FireWeapon(glm::vec3 weaponStartPos, glm::vec3 forward, float fireDistance) {}


		/**
		* @brief Initilises the scene, setting up the terrain and skybox
		*/
		virtual void EnemyFireWeapon(GameObject* enemy, float fireDistance) {}


		/**
		* @brief Sets the players weapon
		*/
		virtual void SetPlayerWeapon(Weapon w) { playerWeapon = w; }


		/**
		* @brief returns the players weapon
		*/
		virtual Weapon GetPlayerWeapon() { return playerWeapon; }

		virtual void SetGameWindow(GlfwWindow* w) { gameWindow = w; }

		/**
		* @brief Saves the game
		*/
		virtual void SaveGame()
		{
			std::ofstream savefile("./res/save.sav");
			if (savefile.is_open())
			{
				switch (singleton<Manager>::getInstance().difficulty)
				{
				case Manager::Difficulty::hard:
					savefile << "hard\n";
					break;
				case Manager::Difficulty::normal:
					savefile << "normal\n";
					break;
				case Manager::Difficulty::easy:
					savefile << "easy\n";
					break;
				default:
					break;
				}

				for (int i = 0; i < gameObjects.size(); i++)
				{
					savefile << gameObjects[i]->StreamValues();
				}
			}

			savefile.close();
		}

		bool loaded;

	protected:

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
		void MakeSaveGameObject(std::string t, std::string script, float scale, float x, float y, float z, float health, float ammo, std::string state, int savedPoints, int savedTokens, int savedKills);
		///The game renderer that renders items
		Renderer* gameRenderer;

		///The scenes name
		std::string sceneName;

		///The game asset factory that creates the different game objects for the scene
		GameAssetFactory* factory;

		///The vector that holds each game object
		std::vector<GameObject*> gameObjects;

		///The games terrain
		Terrain* gameTerrain;

		///The games skybox
		Skybox* gameSkybox;

		GameObject* gameWater;

		///The texture loader for the game
		TextureLoader textureLoader;

		///The viewpoints of the camera and projections
		View lens;

		///The indice of the player game object
		int playerInd;

		///Player Weapon
		Weapon playerWeapon;


		///The exit screen
		ExitScreen exitScreen;

		///If the exit screen is displayed
		bool exitScreenDisplay = false;

		///Game ui pointer
		GameGUI* gameGui;

		///End screen pointer
		EndScreenGUI* endScreenGUI;

		///Main Menu pointer
		MainMenuGUI* mainMenuGui;

		///Spawnpoints vector
		std::vector<glm::vec3> spawnPoints;

		///Water reference index
		int waterIndex;

		glm::vec3 playerStartPosition = glm::vec3(-1000, -1000, -1000);

		PhysicsManager* physicsManager;

		GlfwWindow* gameWindow;
	};

}