#pragma once
#include <string>
#include "GameObjects.h"

enum GameObjectType
{
	TypeStatic,
	TypePlayer,
	TypeEnemy
};


class GameAssetFactory
{
public:
	GameObject* GetGameObject(GameObjectType t, std::string fileName, glm::vec3 position, float scale, glm::vec3 fixRotation, glm::vec3 rotation);
private:
};

