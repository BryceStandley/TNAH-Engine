#pragma once
#include "singleton.h"
#include "state.h"
#include "Debugger.h"

class Player;

class doubleDamage :public State<Player>
{
public:

	/**
	* @brief virtual function that represents the entry point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Enter(Player* dude);

	/**
	* @brief virtual function that represents the execute point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Execute(Player* dude);

	/**
	* @brief virtual function that represents the exit point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Exit(Player* dude);
};

class healthRefill :public State<Player>
{
public:

	/**
	* @brief virtual function that represents the entry point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Enter(Player* dude);

	/**
	* @brief virtual function that represents the execute point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Execute(Player* dude);

	/**
	* @brief virtual function that represents the exit point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Exit(Player* dude);
};

class SpeedUp :public State<Player>
{
public:

	/**
	* @brief virtual function that represents the entry point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Enter(Player* dude);

	/**
	* @brief virtual function that represents the execute point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Execute(Player* dude);

	/**
	* @brief virtual function that represents the exit point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Exit(Player* dude);
};

class doublePoints :public State<Player>
{
public:

	/**
	* @brief virtual function that represents the entry point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Enter(Player* dude);

	/**
	* @brief virtual function that represents the execute point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Execute(Player* dude);

	/**
	* @brief virtual function that represents the exit point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Exit(Player* dude);
};


/**
* @class attack
* @brief A derived class that inherits from the state class. Represents the Attack state of the Enemy FSM
*
* @author Dylan Blereau
* @version 01
* @date 27/04/2021 Dylan Blereau, Started
*
*
**/
class main :public State<Player>
{
public:

	/**
	* @brief virtual function that represents the entry point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Enter(Player* dude);

	/**
	* @brief virtual function that represents the execute point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Execute(Player* dude);

	/**
	* @brief virtual function that represents the exit point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Exit(Player* dude);
};


/**
* @class death
* @brief A derived class that inherits from the state class. Represents the death state of the Player FSM
*
* @author Dylan Blereau
* @version 01
* @date 27/04/2021 Dylan Blereau, Started
*
*
**/
class death :public State<Player>
{
public:

	/**
	* @brief virtual function that represents the entry point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Enter(Player* dude);

	/**
	* @brief virtual function that represents the execute point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Execute(Player* dude);

	/**
	* @brief virtual function that represents the exit point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Exit(Player* dude);
};


/**
* @class global
* @brief A derived class that inherits from the state class. Represents the Global state of the Enemy FSM
*
* @author Dylan Blereau
* @version 01
* @date 27/04/2021 Dylan Blereau, Started
*
*
**/
class glob :public State<Player>
{
public:

	/**
	* @brief virtual function that represents the entry point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Enter(Player* dude);

	/**
	* @brief virtual function that represents the execute point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Execute(Player* dude);

	/**
	* @brief virtual function that represents the exit point of the state
	* @param dude - a pointer to the Enemy object
	*/
	virtual void Exit(Player* dude);
};


/// singletons made for each state ensuring only one instance of each state per FSM 

typedef  singleton<main> main_state;


// tokens
typedef  singleton<doubleDamage> damage_state;
typedef  singleton<healthRefill> health_state;
typedef  singleton<SpeedUp> speed_state;
typedef  singleton<doublePoints> points_state;

// death
typedef  singleton<death> death_state;


// global
typedef  singleton<glob> glob_state;
