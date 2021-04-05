#pragma once
#include <string>
#include "Static.h"
#include "Player.h"
#include "Enemy.h"
#include "Token.h"

enum GameObjectType
{
	TypeStatic,
	TypePlayer,
	TypeEnemy,
	TypeToken
};


class GameAssetFactory
{
public:
	GameAssetFactory(Renderer* r) { renderer = r; playerMade = false; }
	GameObject* GetGameObject(GameObjectType t, std::string modelName, std::string shaderV, std::string shaderF, float scale , glm::vec3 position, bool rotate);
private:
	bool playerMade;
	Renderer* renderer;
};

