#include "Token.h"

void Token::Update(float time)
{
	glm::vec3 r = GetRotation();
	if (r.x >= 360)
		r.x = 0;

	SetRotation(glm::vec3(r.x + GetSpeed() * time, 0, 0));
	SetType("token");
}