#include "Token.h"

void Token::Update(float time)
{
	glm::vec3 r = GetRotation();
	if (r.x >= 360)
		r.x = 0;

	glm::vec3 rot = glm::vec3((r.x + speed) * time, 0, 0);
	SetRotation(rot);
	SetType("token");
}