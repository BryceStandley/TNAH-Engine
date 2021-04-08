#include "Player.h"

void Player::Update(float time)
{
	std::cout << "CAMERA INFO: POS - " << GetPos().x << " " << GetPos().y << " " << GetPos().z << std::endl;
	SetType("player");
}