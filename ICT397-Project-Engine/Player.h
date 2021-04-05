#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player() :GameObject(){}
	void Info() { std::cout << "Pos: X:" << GetPos().x << " -- Y: " << GetPos().y << " -- Z:  " << GetPos().z << std::endl; }
	void Update(float time)
	{
		SetType("player");
	}
};

