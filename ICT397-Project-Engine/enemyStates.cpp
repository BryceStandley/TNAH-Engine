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
	double wanderRadius = 4;
	double wanderDistance = 40;
	double wanderJitter = 5;
	
	float result = atan2(dude->enemyVelocity.z, dude->enemyVelocity.x);
	dude->setWander(wanderRadius, wanderDistance, wanderJitter);

	if (dude->Distance() > 10.0f && dude->Distance() < 25.0f)
	{
		dude->moving = false;
		dude->getFSM()->changeState(&alert_state::getInstance());	
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
		dude->direction = -result;
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
	float result = atan2(dude->velocity.z, dude->velocity.x);

	if (dude->timer < 100)
		dude->timer++;
	else
		dude->getFSM()->changeState(&chase_state::getInstance());

	dude->direction = -result;
}

void alert::Exit(Enemy* dude) 
{
	dude->timer = 0;
}



/******************************************************************************/

void chase::Enter(Enemy* dude)
{
	dude->SetSate(RUN);	
}

void chase::Execute(Enemy* dude)
{
	float result = atan2(dude->velocity.z, dude->velocity.x);

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
		dude->pursue(dude->getCamPos(), pos, dude->velocity, dude->enemyVelocity, dude->GetDeltaTime(), 0.0f);
		dude->SetPos(pos);
	}
	dude->direction = -result;
}

void chase::Exit(Enemy* dude) {}

/******************************************************************************/

void flee::Enter(Enemy* dude)
{
	dude->SetSate(RUN);
}

void flee::Execute(Enemy* dude)
{
	dude->check++;
	
	//std::cout << "CHECK:  " << dude->check << std::endl;

	if (dude->check > 1000)
	{
		//dude->token = false;
		dude->getFSM()->changeState(&die_state::getInstance());
	}

	float res = atan2(-dude->velocity.z, -dude->velocity.x);

	if (dude->Distance() > 10.5f && dude->Distance() < 25.0f && dude->token == false)
	{
		//token has worn off and within chasing distance of player
		dude->getFSM()->changeState(&chase_state::getInstance());
	}
	else if (dude->Distance() < 10.5f && dude->token == false)
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
		dude->evade(pos, dude->getCamPos(), dude->enemyVelocity, dude->velocity, dude->GetDeltaTime());
		dude->SetPos(pos);
		dude->direction = -res;
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
	float res = atan2(dude->velocity.z, dude->velocity.x);

	if (dude->Distance() > 10.5)
	{
		dude->getFSM()->changeState(&chase_state::getInstance());
	}
	else 
	{
		dude->direction = -res;
	}
}

void attack::Exit(Enemy* dude)
{
	dude->SetSate(ATTACK);
}

/******************************************************************************/

void die::Enter(Enemy* dude)
{
	if (dude->deathAnim == false)
	{
		dude->SetSate(DEATH_FALLBACK);
		dude->deathAnim = true;
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
	if (dude->token == true && dude->Distance() < 25 && dude->globalFlag == false) 
	{
		dude->getFSM()->changeState(&flee_state::getInstance());
		dude->globalFlag = true;
	}
	
	if (!dude->isAlive())
		dude->getFSM()->changeState(&die_state::getInstance());
}

void global::Exit(Enemy* dude) {}