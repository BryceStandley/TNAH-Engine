#include "Player.h"

void Player::Update(float time)
{
	singleton<Manager>::getInstance().speed = 10;
}