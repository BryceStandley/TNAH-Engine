#include "playerStates.h"
#include <iostream>
#include "Player.h"
#include <cstdlib>
#include <ctime>

void doubleDamage::Enter(Player* dude)
{
	dude->hasToken = false;
	dude->incrementTokensCollected();
	dude->increasePoints(50);
	dude->setDamage(dude->getDamage() * 2);

    if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "DAMAGE WITH TOKEN: " << dude->getDamage() << std::endl;

	singleton<Manager>::getInstance().prevToken = "DoubleDamage";
	singleton<Manager>::getInstance().token = "none";

}

void doubleDamage::Execute(Player* dude)
{
	if (singleton<Manager>::getInstance().prevToken == "DoubleDamage" && singleton<Manager>::getInstance().timer != 0)
	{
        if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "Token = " << singleton<Manager>::getInstance().prevToken << ", Duration = " << singleton<Manager>::getInstance().timer << std::endl;
	}
	else
	{
        if(Debugger::GetInstance()->debugTokensToConsole)std::cout << "TOKEN EXPIRED" << std::endl;
		dude->getFSM()->changeState(&main_state::getInstance());
	}



	if (singleton<Manager>::getInstance().token == "DoubleDamage" && singleton<Manager>::getInstance().prevToken == "DoubleDamage")
	{
        if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "Token Double Up" << std::endl;
		dude->getFSM()->changeState(&damage_state::getInstance());
	}

	if (singleton<Manager>::getInstance().token == "DoublePoints")
		dude->getFSM()->changeState(&points_state::getInstance());

	if (singleton<Manager>::getInstance().token == "HealthRefill")
		dude->getFSM()->changeState(&health_state::getInstance());

	if (singleton<Manager>::getInstance().token == "SpeedUp")
		dude->getFSM()->changeState(&speed_state::getInstance());
}

void doubleDamage::Exit(Player* dude)
{
	dude->setDamage(dude->getDamage() / 2);
    if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "DAMAGE AFTER TOKEN: " << dude->getDamage();
}

/******************************************************************************/

void healthRefill::Enter(Player* dude)
{
	dude->hasToken = false;
	dude->incrementTokensCollected();
    if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "In Health Refill State" << std::endl;

	dude->increasePoints(50);

	if (dude->getHealth() < 100)
	{
        if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "Healed back to full health" << std::endl;
		dude->setHealth(100);
	}
	else
    if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "Already at full health - no effect" << std::endl;
	
}

void healthRefill::Execute(Player* dude)
{
	dude->getFSM()->changeState(&main_state::getInstance());
}

void healthRefill::Exit(Player* dude)
{
    if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "Exiting Health Refill State" << std::endl;
}

/******************************************************************************/

void SpeedUp::Enter(Player* dude)
{
	dude->hasToken = false;
    if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "This should only happen once mate" << std::endl;
	dude->incrementTokensCollected();
	dude->increasePoints(50);

	singleton<Manager>::getInstance().prevToken = "SpeedUp";
	singleton<Manager>::getInstance().token = "none";
}

void SpeedUp::Execute(Player* dude)
{
	
	if (singleton<Manager>::getInstance().prevToken == "SpeedUp" && singleton<Manager>::getInstance().timer != 0)
	{
		singleton<Manager>::getInstance().speed = 10;
        if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "Token = " << singleton<Manager>::getInstance().prevToken << ", Duration = " << singleton<Manager>::getInstance().timer << std::endl;
	}
	else
	{
        if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "TOKEN EXPIRED" << std::endl;
		singleton<Manager>::getInstance().speed = 5;
		dude->getFSM()->changeState(&main_state::getInstance());
	}

	

	if (singleton<Manager>::getInstance().token == "SpeedUp" && singleton<Manager>::getInstance().prevToken == "SpeedUp") 
	{
        if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "Token Double Up" << std::endl;
		dude->getFSM()->changeState(&speed_state::getInstance());
	}

	if (singleton<Manager>::getInstance().token == "DoublePoints")
		dude->getFSM()->changeState(&points_state::getInstance());

	if (singleton<Manager>::getInstance().token == "HealthRefill")
		dude->getFSM()->changeState(&health_state::getInstance());

	if (singleton<Manager>::getInstance().token == "DoubleDamage")
		dude->getFSM()->changeState(&damage_state::getInstance());
}

void SpeedUp::Exit(Player* dude)
{
	singleton<Manager>::getInstance().speed = 5;
}

/******************************************************************************/

void doublePoints::Enter(Player* dude)
{
	dude->hasToken = false;
	dude->incrementTokensCollected();
    if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "In Double Points State" << std::endl;

	dude->increasePoints(50);

	dude->setMultiplier(2);

	singleton<Manager>::getInstance().prevToken = "DoublePoints";
	singleton<Manager>::getInstance().token = "none";
}

void doublePoints::Execute(Player* dude)
{
	if (singleton<Manager>::getInstance().prevToken == "DoublePoints" && singleton<Manager>::getInstance().timer != 0) 
	{
        if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "Token = " << singleton<Manager>::getInstance().prevToken << ", Duration = " << singleton<Manager>::getInstance().timer << std::endl;
	}
	else
		dude->getFSM()->changeState(&main_state::getInstance());

	if (singleton<Manager>::getInstance().token == "DoublePoints" && singleton<Manager>::getInstance().prevToken == "DoublePoints")
	{
        if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "Token Double Up" << std::endl;
		dude->getFSM()->changeState(&points_state::getInstance());
	}

	if (singleton<Manager>::getInstance().token == "SpeedUp")
		dude->getFSM()->changeState(&speed_state::getInstance());

	if (singleton<Manager>::getInstance().token == "HealthRefill")
		dude->getFSM()->changeState(&health_state::getInstance());

	if (singleton<Manager>::getInstance().token == "DoubleDamage")
		dude->getFSM()->changeState(&damage_state::getInstance());
}

void doublePoints::Exit(Player* dude)
{
    if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "Double Points State" << std::endl;
	dude->setMultiplier(1); //resets multiplier
}

/******************************************************************************/

void death::Enter(Player* dude)
{
}

void death::Execute(Player* dude)
{
    if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "DEAD" << std::endl;
	//display score menu 
}

void death::Exit(Player* dude) {}

/******************************************************************************/

void main::Enter(Player* dude)
{
	dude->hasToken = true;
	std::cout << "TOTAL POINTS " << dude->getPoints() << std::endl;
	std::cout << "TOKENS COLLECTED " << dude->getTokensCollected() << std::endl;
	std::cout << "KILL COUNT " << dude->getKills() << std::endl;
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