#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
public:
	void Update(float time)
	{
		SetType("enemy");
		glm::vec3 r = GetRotation();
		SetRotation(glm::vec3(0, r.y + time, 0));
	}
};

