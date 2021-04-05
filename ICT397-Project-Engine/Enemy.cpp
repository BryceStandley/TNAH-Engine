#include "Enemy.h"

void Enemy::Update(float time)
{
	SetType("enemy");
	glm::vec3 r = GetRotation();
	SetRotation(glm::vec3(0, r.y + time, 0));
}