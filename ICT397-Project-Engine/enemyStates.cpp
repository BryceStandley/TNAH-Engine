#include "enemyStates.h"
#include <iostream>
#include "Enemy.h"
#include <cstdlib>
#include <ctime>


/******************************************************************************/

void wander::Enter(Enemy* dude)
{
	dude->SetSate(WALK);
	std::cout << "WALKING" << std::endl;	
}

void wander::Execute(Enemy* dude)
{
	if (dude->getToken() == true && dude->getFSM()->getPreviousState() == &flee_state::getInstance()) 
	{
		dude->incrementCheck();
		std::cout << "CHECK:  " << dude->getCheck() << std::endl;
	}
		

	if (dude->getCheck() > 1000 && dude->getToken() == true)
	{
		dude->setToken(false);
		//dude->setGlobalFlag(false);
		//dude->getFSM()->changeState(&die_state::getInstance());
	}

	std::cout << "WANDER" << std::endl;
	double wanderRadius = 5;
	double wanderDistance = 35;
	double wanderJitter = 1;
	
	float result = atan2(dude->enemyVelocity.z, dude->enemyVelocity.x);
	dude->setWander(wanderRadius, wanderDistance, wanderJitter);

	if (dude->Distance() > 10.0f && dude->Distance() < 25.0f && dude->getToken() == false)
	{
		dude->moving = false;
		dude->getFSM()->changeState(&alert_state::getInstance());	
	}
	else if (dude->Distance() > 10.0f && dude->Distance() < 25.0f && dude->getToken() == true)
	{
		dude->getFSM()->changeState(&flee_state::getInstance());
	}
	else if (dude->moving)
	{
		glm::vec3 curPos = dude->GetPos();
		if (dude->moveTo(curPos, dude->newPos, dude->enemyVelocity, dude->GetDeltaTime(), 0))
			dude->moving = false;
		else
		{
			dude->direction = -result;
			dude->SetPos(curPos);
		}
	}
	else 
	{
		glm::vec3 pos(dude->GetPos());

		dude->wander(pos, dude->enemyVelocity, dude->GetDeltaTime());
		dude->SetPos(pos);
		dude->setDirection(-result);
	}
}

void wander::Exit(Enemy* dude) {}


/******************************************************************************/

void alert::Enter(Enemy* dude)
{
	dude->SetSate(POINTING);
	singleton<MessageDispatcher>::getInstance().DisbatchMsgAllOfType(dude->GetId(), 1, "enemy");
	//this will then send a message out to other enemies within a distance 
	// NOTE - It would be wise that when the message is sent, that it only affects enemies that aren't already in the alert OR chase state. 
}

void alert::Execute(Enemy* dude)
{
	std::cout << "ALERT" << std::endl;
	float result = atan2(dude->getVelocity().z, dude->getVelocity().x);

	if (dude->getTimer() < 100)
		dude->incrementTimer();
	else
		dude->getFSM()->changeState(&chase_state::getInstance());

	dude->setDirection(-result);
}

void alert::Exit(Enemy* dude) 
{
	dude->setTimer(0);
}


/******************************************************************************/

void chase::Enter(Enemy* dude)
{
	dude->SetSate(RUN);	
}

void chase::Execute(Enemy* dude)
{
	std::cout << "CHASE" << std::endl;
	float result = atan2(dude->getVelocity().z, dude->getVelocity().x);

	if (dude->Distance() < 10)
	{
		dude->getFSM()->changeState(&attack_state::getInstance());
	}
	else if (dude->Distance() > 25.0f)
	{
		dude->getFSM()->changeState(&wander_state::getInstance());
	}
	else 
	{
		glm::vec3 pos(dude->GetPos());
		glm::vec3 vel(dude->getEnemyVelocity());

		dude->pursue(dude->getCamPos(), pos, dude->getVelocity(), vel, dude->GetDeltaTime(), 0.0f);
		dude->SetPos(pos);
	}
	dude->setDirection(-result);
}

void chase::Exit(Enemy* dude) {}

/******************************************************************************/

void flee::Enter(Enemy* dude)
{
	dude->SetSate(RUN);
}

void flee::Execute(Enemy* dude)
{
	std::cout << "FLEE" << std::endl;
	dude->incrementCheck();
	//std::cout << dude->incrementCheck() << std::endl;
	std::cout << "CHECK:  " << dude->getCheck() << std::endl;

	if (dude->getCheck() > 1000)
	{
		dude->setToken(false);
		//dude->globalFlag = false;
		//dude->getFSM()->changeState(&die_state::getInstance());
	}

	float res = atan2(-dude->getVelocity().z, -dude->getVelocity().x);

	if (dude->Distance() > 10.5f && dude->Distance() < 25.0f && dude->getToken() == false)
	{
		//token has worn off and within chasing distance of player
		dude->getFSM()->changeState(&chase_state::getInstance());
	}
	else if (dude->Distance() < 10.5f && dude->getToken() == false)
	{
		//token has worn off and within shooting distance
		dude->getFSM()->changeState(&attack_state::getInstance());
	}
	else if (dude->Distance() > 25.0f)
	{
		//std::cout << "far enough away now" << std::endl;
		dude->getFSM()->changeState(&wander_state::getInstance());
	}
	else
	{
		glm::vec3 pos(dude->GetPos());
		glm::vec3 vel(dude->getEnemyVelocity());
		dude->evade(pos, dude->getCamPos(), vel, dude->getVelocity(), dude->GetDeltaTime());
		dude->SetPos(pos);
		dude->setDirection(-res);
	}		
}

void flee::Exit(Enemy* dude) {}

/******************************************************************************/

void attack::Enter(Enemy* dude)
{
	dude->SetSate(ATTACK);
}

void attack::Execute(Enemy* dude)
{
	std::cout << "ATTACK" << std::endl;
	float res = atan2(dude->getVelocity().z, dude->getVelocity().x);

	if (dude->Distance() > 10.5)
	{
		dude->getFSM()->changeState(&chase_state::getInstance());
	}
	else 
	{
		dude->setDirection(-res);
	}
}

void attack::Exit(Enemy* dude)
{
	dude->SetSate(ATTACK);
}

/******************************************************************************/

void die::Enter(Enemy* dude)
{
	std::cout << "DIE" << std::endl;
	if (dude->getDeathAnim() == false)
	{
		dude->SetSate(DEATH_FALLBACK);
		dude->setDeathAnim(true);
		dude->getFSM()->changeState(&die_state::getInstance());
	}
	else
		dude->SetSate(DEATH);		
}

void die::Execute(Enemy* dude) 
{
	dude->killFSM = true;
}

void die::Exit(Enemy* dude) {}

/******************************************************************************/

void global::Enter(Enemy* dude) {}

void global::Execute(Enemy* dude)
{
	if (dude->getToken() == true && dude->Distance() < 25 && dude->getGlobalFlag() == false) 
	{
		std::cout << "GLOBAL" << std::endl;
		dude->getFSM()->changeState(&flee_state::getInstance());
		dude->setGlobalFlag(true);	///kills the repeat entry
	}
	if (!dude->isAlive())
		dude->getFSM()->changeState(&die_state::getInstance());
}

void global::Exit(Enemy* dude) {}