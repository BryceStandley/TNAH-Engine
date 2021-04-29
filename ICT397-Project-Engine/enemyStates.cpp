#include "enemyStates.h"
#include <iostream>
#include "Enemy.h"
#include <cstdlib>
#include <ctime>

// Use Wander as an idle function for now. 
/******************************************************************************/
void wander::Enter(Enemy* dude)
{
	std::cout << "Entering wander state" << std::endl;
	dude->SetSate(SALUTE);
	srand(static_cast<unsigned>(time(0)));
	//start animation = STAND (could use walk animation which would be a slowed down run).
}

void wander::Execute(Enemy* dude)
{
	if (dude->Distance() > 10.5f && dude->Distance() < 25.0f)
	{
		std::cout << "ahh fuck there's Zoom Girl. Gotta chase her" << std::endl;
		dude->getFSM()->changeState(&chase_state::getInstance());
	}
	
	//WANDER CODE GOES HERE

}

void wander::Exit(Enemy* dude)
{
	std::cout << "exiting wander state" << std::endl;
}

/******************************************************************************/
void chase::Enter(Enemy* dude)
{
	std::cout << "Entering chase state" << std::endl;
	srand(static_cast<unsigned>(time(0)));
	dude->SetSate(RUN);
	//start animation = RUN
}

void chase::Execute(Enemy* dude)
{

	if (dude->Distance())
	{
		std::cout << "reached her, time to shoot" << std::endl;
		dude->getFSM()->changeState(&attack_state::getInstance());
	}
	else if (dude->Distance())
	{
		std::cout << "lost her - time to stop" << std::endl;
		dude->getFSM()->changeState(&wander_state::getInstance());
	}
	else 
	{
		std::cout << "chasing..." << std::endl;
	}

	//CHASE CODE GOES IN THIS FUNCTION

}

void chase::Exit(Enemy* dude)
{
	std::cout << "exiting chase state" << std::endl;
}

/******************************************************************************/
void flee::Enter(Enemy* dude)
{
	std::cout << "entered flee state" << std::endl;

	//start animation = RUN
}

void flee::Execute(Enemy* dude)
{
	float distance = 24.0f;
	
	if (dude->Distance() && dude->Distance() && !dude->hasToken())
	{
		//token has worn off and within chasing distance of player
		std::cout << "token worn off- within chasing distance" << std::endl;
		dude->getFSM()->changeState(&chase_state::getInstance());
	}
	else if (dude->Distance() && dude->hasToken() == false)
	{
		std::cout << "token worn off - within shooting distance" << std::endl;
		dude->getFSM()->changeState(&attack_state::getInstance());
	}
	else if (dude->Distance() > 25.0f)
	{
		std::cout << "far enough away now" << std::endl;
		dude->getFSM()->changeState(&wander_state::getInstance());
	}
	else
	{
		std::cout << "running away..." << std::endl;
	}
/*
	double f = rand() % 10 * .1;
	if (f > 0.25) 
	{
		dude->hasToken() == false;

		if (dude->hasToken() == false) 
		{
			std::cout << "Safe to attack her now!" << std::endl;
			dude->getFSM()->changeState(&attack_state::getInstance());
		}

	}
	else 
	{
		std::cout << "okay i got away " << std::endl;
		dude->getFSM()->changeState(&wander_state::getInstance());
	}
*/
	//FLEE CODE GOES HERE 
		
}

void flee::Exit(Enemy* dude)
{
	std::cout << "leaving flee state" << std::endl;
}

/******************************************************************************/
void attack::Enter(Enemy* dude)
{
	std::cout << "entered attack state" << std::endl;
	dude->SetSate(ATTACK);
	//start animation = ATTACK
}

void attack::Execute(Enemy* dude)
{
	if (dude->Distance() > 10.5)
	{
		std::cout << "COME BACK HERE" << std::endl;
		dude->getFSM()->changeState(&chase_state::getInstance());
	}
	else 
	{
		std::cout << "shooting at her .." << std::endl;
		//std::cout << "she hit me OUCH" << std::endl;
		//dude->Damage(-10);
	}



	//if within 
	//if (dude->hasToken() == true)
	//{
	//	std::cout << "FUCK, she is overpowered boys" << std::endl;
	//	dude->getFSM()->changeState(&flee_state::getInstance());
	//}
	//else if (dude->hasToken() == false);
	//{
	//	std::cout << "shooting at her .." << std::endl;
	//	std::cout << "she hit me OUCH" << std::endl;
	//	dude->decreaseHealth(10);

	//}
		
}

void attack::Exit(Enemy* dude)
{
	std::cout << "leaving attack state" << std::endl;
}

/******************************************************************************/
void die::Enter(Enemy* dude)
{
	std::cout << "ARGHHH FUCK I DIED" << std::endl;

	// do death animation here.
	//remove/unload enemy model

}

void die::Execute(Enemy* dude)
{	
	dude->killFSM = true;
}

void die::Exit(Enemy* dude) {}

/******************************************************************************/
void global::Enter(Enemy* dude)
{
	
}

void global::Execute(Enemy* dude)
{
	if (dude->hasToken() == true)
		dude->getFSM()->changeState(&flee_state::getInstance());

	if (!dude->isAlive())
		dude->getFSM()->changeState(&die_state::getInstance());
}

void global::Exit(Enemy* dude) {}