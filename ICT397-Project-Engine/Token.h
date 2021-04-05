#pragma once
#include "GameObject.h"
class Token : public GameObject
{
public:
	void Update(float time)
	{
		glm::vec3 r = GetRotation();
		SetRotation(glm::vec3(r.x + time, 0, 0));
		SetType("token");
	}
};

