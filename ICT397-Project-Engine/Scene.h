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
	Player player;
	Scene(std::string name) {}
	Scene(std::string name, std::string fs, std::string vs, std::string t);
	~Scene();
	void Run(View lens);
	bool Init(std::string fs, std::string vs, std::string t);
	Terrain *GetTerrain() { return gameTerrain; }
	Skybox* GetSkybox() { return gameSkybox; }
	std::string GetSceneName() const { return sceneName; }
	GameObject *MakeGameObject(std::string modelName, std::string shaderV, std::string shaderF, float s, glm::vec3 p, bool rotate);
	GameObject *GetGameObject(int i) { return gameObjects[i]; }
	void UpdatePlayer(glm::vec3 position);
	void SetupTerrain();
	int GetPlayerIndice() { return playerInd; }
	Renderer* gameRenderer;
private:
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

	int playerInd;
};

