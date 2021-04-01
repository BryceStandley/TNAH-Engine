#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player() :GameObject(){}
	void Info() { std::cout << "Pos" << GetPos().x << " " << GetPos().y << " " << GetPos().z << std::endl; }
};

