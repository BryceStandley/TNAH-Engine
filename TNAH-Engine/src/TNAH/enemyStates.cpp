#include "tnahpch.h"
#include "enemyStates.h"
#include "Enemy.h"
#include <cstdlib>
#include <ctime>


/******************************************************************************/

void wander::Enter(Enemy* dude)
{
	if (dude->wanderLua.isTable())
	{
		dude->wanderLua[1](dude);
	}
}

void wander::Execute(Enemy* dude)
{
	if (dude->wanderLua.isTable())
	{
		dude->wanderLua[2](dude);
	}
}

void wander::Exit(Enemy* dude) {
	if (dude->wanderLua.isTable())
	{
		dude->wanderLua[3](dude);
	}
}


/******************************************************************************/

void alert::Enter(Enemy* dude)
{
	if (dude->alert.isTable())
	{
		dude->alert[1](dude);
	}
}

void alert::Execute(Enemy* dude)
{
	if (dude->alert.isTable())
	{
		dude->alert[2](dude);
	}
}

void alert::Exit(Enemy* dude) 
{
	if (dude->alert.isTable())
	{
		dude->alert[3](dude);
	}
}


/******************************************************************************/

void chase::Enter(Enemy* dude)
{
	if (dude->chase.isTable())
	{
		dude->chase[1](dude);
	}
}

void chase::Execute(Enemy* dude)
{
	if (dude->chase.isTable())
	{
		dude->chase[2](dude);
	}
}

void chase::Exit(Enemy* dude)
{
	if (dude->chase.isTable())
	{
		dude->chase[3](dude);
	}
}

/******************************************************************************/

void flee::Enter(Enemy* dude)
{
	if (dude->fleeLua.isTable())
	{
		dude->fleeLua[1](dude);
	}
}

void flee::Execute(Enemy* dude)
{
	if (dude->fleeLua.isTable())
	{
		dude->fleeLua[2](dude);
	}
}

void flee::Exit(Enemy* dude)
{
	if (dude->fleeLua.isTable())
	{
		dude->fleeLua[3](dude);
	}
}

/******************************************************************************/

void attack::Enter(Enemy* dude)
{
	if (dude->attack.isTable())
	{
		dude->attack[1](dude);
	}
}

void attack::Execute(Enemy* dude)
{
	if (dude->attack.isTable())
	{
		dude->attack[2](dude);
	}
}

void attack::Exit(Enemy* dude)
{
	if (dude->attack.isTable())
	{
		dude->attack[3](dude);
	}
}

/******************************************************************************/

void die::Enter(Enemy* dude)
{
	if (dude->die.isTable())
	{
		dude->die[1](dude);
	}
}

void die::Execute(Enemy* dude) 
{
	if (dude->die.isTable())
	{
		dude->die[2](dude);
	}
}

void die::Exit(Enemy* dude)
{
	if (dude->die.isTable())
	{
		dude->die[3](dude);
	}
}

/******************************************************************************/

void global::Enter(Enemy* dude)
{
	if (dude->global.isTable())
	{
		dude->global[1](dude);
	}
}

void global::Execute(Enemy* dude)
{
	if (dude->global.isTable())
	{
		dude->global[2](dude);
	}
}

void global::Exit(Enemy* dude)
{
	if (dude->global.isTable())
	{
		dude->global[3](dude);
	}
}