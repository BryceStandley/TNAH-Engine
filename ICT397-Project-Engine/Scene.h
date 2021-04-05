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
	void Run(View lens);

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
		* @param modalName - the file path to load in the model
		* @param shaderV - The vertex shader file path
		* @param shaderF - The fragment shader file path
		* @param scale - The scale of the object
		* @param x - The x positon of the object
		* @param y - The y position of the object
		* @param z - The z position of the object
		* @param rotate - Sets if the model needs to be rotated on entry
		*/
	void MakeGameObject(std::string t, std::string modelName, std::string shaderV, std::string shaderF, float scale, float x, float y, float z, bool rotate);

		/**
		* @brief Gets a gameobject from the game objects
		* @param i - The indice of the game object
		*/
	GameObject *GetGameObject(int i) { return gameObjects[i]; }

		/**
		* @brief Updates the players position in relation to the world
		* @param position - The position of the camera
		*/
	void UpdatePlayer(glm::vec3 position);

		/**
		* @brief Gets the playerInd value and returns it
		*/
	int GetPlayerIndice() { return playerInd; }

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
};

