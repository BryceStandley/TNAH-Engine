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
	Renderer* gameRenderer;
private:
	std::string sceneName;
	GameAssetFactory factory;
	std::vector<GameObject*> gameObjects;
	Terrain *gameTerrain;
	Skybox* gameSkybox;
	TextureLoader textureLoader;
	View lens;
};

