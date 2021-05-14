#include "playerStates.h"
#include <iostream>
#include "Player.h"
#include <cstdlib>
#include <ctime>

void token::Enter(Player* dude)
{
	std::cout << "In Token State" << std::endl;
	if (dude->token == 0)
	{
		//singleton<Manager>::getInstance().speed = 10;

		std::cout << dude->getPoints() << std::endl;
		dude->increasePoints(50);
		std::cout << dude->getPoints() << std::endl;
	}

	if (dude->token == 1)
	{
		dude->increasePoints(50);

		dude->setMultiplier(2);
		
	}


	if (dude->token == 2)
	{
		dude->increasePoints(50);

		if (dude->getHealth() < 100)
		{
			std::cout << "Healed back to full health" << std::endl;
			dude->setHealth(100);
		}
		else
			std::cout << "Already at full health - no effect" << std::endl;
	}
		

	
}

void token::Execute(Player* dude)
{
	if (dude->token == 0) 
	{
		if (singleton<Manager>::getInstance().token == "SpeedUp" && singleton<Manager>::getInstance().timer != 0)
		{
			singleton<Manager>::getInstance().speed = 10;
            if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "Token = " << singleton<Manager>::getInstance().token << ", Duration = " << singleton<Manager>::getInstance().timer << std::endl;
			//dude->increasePoints(50);
		}
		else
		{
            if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "TOKEN EXPIRED" << std::endl;
			singleton<Manager>::getInstance().speed = 5;
			dude->getFSM()->changeState(&glob_state::getInstance());
		}

	}

	if (dude->token == 1) 
	{
		if (singleton<Manager>::getInstance().timer != 0)
        {
            if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "Token = " << singleton<Manager>::getInstance().token << ", Duration = " << singleton<Manager>::getInstance().timer << std::endl;
        }
        else
        {
            dude->getFSM()->changeState(&glob_state::getInstance());
        }
	}

	if (dude->token == 2) 
	{
		dude->getFSM()->changeState(&glob_state::getInstance());
	}

	
	
}

void token::Exit(Player* dude)
{
	//singleton<Manager>::getInstance().speed = 5;
}

/******************************************************************************/

void death::Enter(Player* dude)
{
	std::cout << "test" << std::endl;
}

void death::Execute(Player* dude)
{
	//dude->killFSM = true;
}

void death::Exit(Player* dude) {}

/******************************************************************************/

void glob::Enter(Player* dude) 
{
    if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "Global State" << std::endl;
    if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "TOTAL POINTS = " << dude->getPoints() << std::endl;
}

void glob::Execute(Player* dude)
{
	//dude->setHealth(10);
	if (singleton<Manager>::getInstance().token == "SpeedUp")
	{
		dude->hasToken = true;
		dude->token = 0;
		dude->getFSM()->changeState(&token_state::getInstance());	
	}

	if (singleton<Manager>::getInstance().token == "DoublePoints")
	{
		dude->hasToken = true;
		dude->token = 1;
		dude->getFSM()->changeState(&token_state::getInstance());
	}

	if(singleton<Manager>::getInstance().token == "HealthRefill")
	{
		dude->hasToken = true;
		dude->token = 2;
		dude->getFSM()->changeState(&token_state::getInstance());
	}

	

}

void glob::Exit(Player* dude) {}