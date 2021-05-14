#include "playerStates.h"
#include <iostream>
#include "Player.h"
#include <cstdlib>
#include <ctime>

void doubleDamage::Enter(Player* dude)
{
	dude->hasToken = false;
	dude->increasePoints(50);
	dude->setDamage(dude->getDamage() * 2);

}

void doubleDamage::Execute(Player* dude)
{
	std::cout << dude->getDamage();

}

void doubleDamage::Exit(Player* dude)
{
	dude->setDamage(dude->getDamage() / 2);
	std::cout << dude->getDamage();
}

/******************************************************************************/

void healthRefill::Enter(Player* dude)
{
	dude->hasToken = false;
	std::cout << "In Health Refill State" << std::endl;

	dude->increasePoints(50);

	if (dude->getHealth() < 100)
	{
		std::cout << "Healed back to full health" << std::endl;
		dude->setHealth(100);
	}
	else
		std::cout << "Already at full health - no effect" << std::endl;
	
}

void healthRefill::Execute(Player* dude)
{
	dude->getFSM()->changeState(&main_state::getInstance());
}

void healthRefill::Exit(Player* dude)
{
	std::cout << "Exiting Health Refill State" << std::endl;
}

/******************************************************************************/

void SpeedUp::Enter(Player* dude)
{
	dude->hasToken = false;
	std::cout << "This should only happen once mate" << std::endl;
	dude->increasePoints(50);
}

void SpeedUp::Execute(Player* dude)
{
	if (singleton<Manager>::getInstance().token == "SpeedUp" && singleton<Manager>::getInstance().timer != 0)
	{
		singleton<Manager>::getInstance().speed = 10;
		std::cout << "Token = " << singleton<Manager>::getInstance().token << ", Duration = " << singleton<Manager>::getInstance().timer << std::endl;
	}
	else
	{
		std::cout << "TOKEN EXPIRED" << std::endl;
		singleton<Manager>::getInstance().speed = 5;
		dude->getFSM()->changeState(&main_state::getInstance());
	}
}

void SpeedUp::Exit(Player* dude)
{
	singleton<Manager>::getInstance().speed = 5;
}

/******************************************************************************/

void doublePoints::Enter(Player* dude)
{
	dude->hasToken = false;
	std::cout << "In Double Points State" << std::endl;

	dude->increasePoints(50);

	dude->setMultiplier(2);
}

void doublePoints::Execute(Player* dude)
{
	if (singleton<Manager>::getInstance().timer != 0)
		std::cout << "Token = " << singleton<Manager>::getInstance().token << ", Duration = " << singleton<Manager>::getInstance().timer << std::endl;
	else
		dude->getFSM()->changeState(&main_state::getInstance());
}

void doublePoints::Exit(Player* dude)
{
	std::cout << "Double Points State" << std::endl;
	dude->setMultiplier(1); //resets multiplier
}

/******************************************************************************/

void death::Enter(Player* dude)
{
}

void death::Execute(Player* dude)
{
	std::cout << "DEAD" << std::endl;
	//display score menu 
}

void death::Exit(Player* dude) {}

/******************************************************************************/

void main::Enter(Player* dude)
{
	dude->hasToken = true;
	std::cout << "TOTAL POINTS" << dude->getPoints() << std::endl;
}

void main::Execute(Player* dude)
{
}

void main::Exit(Player* dude)
{

}

/******************************************************************************/

void glob::Enter(Player* dude) 
{
	std::cout << "Global State" << std::endl;
}

void glob::Execute(Player* dude)
{
	if (singleton<Manager>::getInstance().token == "SpeedUp" && dude->hasToken == true)
	{	
		dude->getFSM()->changeState(&speed_state::getInstance());	
	}

	if (singleton<Manager>::getInstance().token == "DoublePoints" && dude->hasToken == true)
	{

		dude->getFSM()->changeState(&points_state::getInstance());
	}

	if(singleton<Manager>::getInstance().token == "HealthRefill" && dude->hasToken == true)
	{
		dude->getFSM()->changeState(&health_state::getInstance());
	}

	if (singleton<Manager>::getInstance().token == "DoubleDamage" && dude->hasToken == true)
	{
		dude->getFSM()->changeState(&damage_state::getInstance());
	}

	if (dude->getHealth() == 0) 
	{
		dude->getFSM()->changeState(&death_state::getInstance());
	}

}

void glob::Exit(Player* dude) {}