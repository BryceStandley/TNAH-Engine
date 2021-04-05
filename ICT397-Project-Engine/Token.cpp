#include "Token.h"

void Token::Update(float time)
{
	glm::vec3 r = GetRotation();
	SetRotation(glm::vec3(r.x + time, 0, 0));
	SetType("token");
}