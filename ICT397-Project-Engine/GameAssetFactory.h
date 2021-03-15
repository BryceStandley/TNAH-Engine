#pragma once
#include <string>
#include "GameObject.h"

class GameAssetFactory
{
public:
	GameObject GetGameObject(std::string objectType);
private:

};

