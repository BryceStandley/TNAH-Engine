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
	dude->SetSate(WALK);
	srand(static_cast<unsigned>(time(0)));
	dude->globalFlag = false;
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
	float result = atan2(dude->velocity.z, dude->velocity.x);

	if (dude->Distance() < 10.5)
	{
		std::cout << "reached her, time to shoot" << std::endl;
		dude->getFSM()->changeState(&attack_state::getInstance());
	}
	else if (dude->Distance() > 25.0f)
	{
		std::cout << "lost her - time to stop" << std::endl;
		dude->getFSM()->changeState(&wander_state::getInstance());
	}
	else 
	{
		std::cout << "chasing..." << std::endl;
		glm::vec3 pos(dude->GetPos());
		pos.x += (dude->velocity.x * 0.005);
		pos.z += (dude->velocity.z * 0.005);
		dude->SetPos(pos);

		
	}
	dude->direction = -result;
}

void chase::Exit(Enemy* dude)
{
	std::cout << "exiting chase state" << std::endl;
}

/******************************************************************************/
void flee::Enter(Enemy* dude)
{
	std::cout << "entered flee state" << std::endl;
	srand(static_cast<unsigned>(time(0)));
	dude->SetSate(RUN);
	//start animation = RUN
}

void flee::Execute(Enemy* dude)
{
	dude->check++;
	
	//std::cout << "CHECK:  " << dude->check << std::endl;

	if (dude->check > 1000)
	{
		dude->token = false;	
	}

	float res = atan2(-dude->velocity.z, -dude->velocity.x);

	if (dude->Distance() > 10.5f && dude->Distance() < 25.0f && dude->token == false)
	{
		//token has worn off and within chasing distance of player
		std::cout << "token worn off- within chasing distance" << std::endl;
		dude->getFSM()->changeState(&chase_state::getInstance());
	}
	else if (dude->Distance() < 10.5f && dude->token == false)
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
		dude->velocity.y = 0.0f;

		glm::vec3 pos(dude->GetPos());
		pos -= (dude->velocity * (0.005f));
		
		dude->SetPos(pos);
		dude->direction = -res;
	}		
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
	float res = atan2(dude->velocity.z - 0.7f, dude->velocity.x);

	if (dude->Distance() > 10.5)
	{
		std::cout << "COME BACK HERE" << std::endl;
		dude->getFSM()->changeState(&chase_state::getInstance());
	}
	else 
	{
		std::cout << "shooting at her .." << std::endl;
		dude->direction = -res;
	}
	
		
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
	if (dude->token == true && dude->Distance() < 25 && dude->globalFlag == false) 
	{
		dude->getFSM()->changeState(&flee_state::getInstance());
		dude->globalFlag = true;
	}
	
	if (!dude->isAlive())
		dude->getFSM()->changeState(&die_state::getInstance());
}

void global::Exit(Enemy* dude) {}