#pragma once
#include "GameObject.h"
class Static : public GameObject
{
public:
	void Update(float time)
	{
		SetType("static");
	}
};

