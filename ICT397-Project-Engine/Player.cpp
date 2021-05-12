#include "Player.h"

void Player::Update(float time)
{
	if (singleton<Manager>::getInstance().token == "SpeedUp")
		singleton<Manager>::getInstance().speed = 10;
	else
		singleton<Manager>::getInstance().speed = 5;
	std::cout << "Token = " << singleton<Manager>::getInstance().token << ", Duration = " << singleton<Manager>::getInstance().timer << std::endl;
}