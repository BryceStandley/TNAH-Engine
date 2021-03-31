#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player() :GameObject(){}
	//Player(glm::vec3 pos, float colSize, float objSize) :GameObject(pos, colSize, objSize) {}
	void onCollision(GameObject& collisionObject) {}
};

