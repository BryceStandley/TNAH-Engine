#include "Enemy.h"

void Enemy::Update(float time)
{
	SetType("enemy");
	enemyFSM->update();
}