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
	GameObject* GetGameObject(GameObjectType t);
private:
};

