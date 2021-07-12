#include "tnahpch.h"
#include "playerStates.h"
#include "Player.h"


void doubleDamage::Enter(Player* dude)
{
	if (dude->dd.isTable())
	{
		dude->dd[1](dude);
	}
}

void doubleDamage::Execute(Player* dude)
{
	if (dude->dd.isTable())
	{
		dude->dd[2](dude);
	}
}

void doubleDamage::Exit(Player* dude)
{
	if (dude->dd.isTable())
	{
		dude->dd[3](dude);
	}
}

/******************************************************************************/

void healthRefill::Enter(Player* dude)
{
	if (dude->refill.isTable())
	{
		dude->refill[1](dude);
	}
}

void healthRefill::Execute(Player* dude)
{
	if (dude->refill.isTable())
	{
		dude->refill[2](dude);
	}
}

void healthRefill::Exit(Player* dude)
{
	if (dude->refill.isTable())
	{
		dude->refill[3](dude);
	}
}

/******************************************************************************/

void SpeedUp::Enter(Player* dude)
{
	if (dude->speedBoost.isTable())
	{
		dude->speedBoost[1](dude);
	}
}

void SpeedUp::Execute(Player* dude)
{
	
	if (dude->speedBoost.isTable())
	{
		dude->speedBoost[2](dude);
	}
}

void SpeedUp::Exit(Player* dude)
{
	if (dude->speedBoost.isTable())
	{
		dude->speedBoost[3](dude);
	}
}

/******************************************************************************/

void doublePoints::Enter(Player* dude)
{
	if (dude->dp.isTable())
	{
		dude->dp[1](dude);
	}
}

void doublePoints::Execute(Player* dude)
{
	if (dude->dp.isTable())
	{
		dude->dp[2](dude);
	}
}

void doublePoints::Exit(Player* dude)
{
	if (dude->dp.isTable())
	{
		dude->dp[3](dude);
	}
}

/******************************************************************************/

void deathState::Enter(Player* dude)
{
	if (dude->death.isTable())
	{
		dude->death[1](dude);
	}
}

void deathState::Execute(Player* dude)
{
	if (dude->death.isTable())
	{
		dude->death[2](dude);
	}
}

void deathState::Exit(Player* dude)
{	
	if (dude->death.isTable())
	{
		dude->death[3](dude);
	}
}

/******************************************************************************/

void main::Enter(Player* dude)
{
	if (dude->mainState.isTable())
	{
		dude->mainState[1](dude);
	}
}

void main::Execute(Player* dude)
{
	if (dude->mainState.isTable())
	{
		dude->mainState[2](dude);
	}
}

void main::Exit(Player* dude)
{
	if (dude->mainState.isTable())
	{
		dude->mainState[3](dude);
	}
}

/******************************************************************************/

void glob::Enter(Player* dude) 
{
	if (dude->global.isTable())
	{
		dude->global[1](dude);
	}
}

void glob::Execute(Player* dude)
{
	if (dude->global.isTable())
	{
		dude->global[2](dude);
	}

}

void glob::Exit(Player* dude)
{
	if (dude->global.isTable())
	{
		dude->global[3](dude);
	}
}