#pragma once
#include "singleton.h"
#include "state.h"
#include "Debugger.h"

class Player;


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
class token :public State<Player>
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
* @class die
* @brief A derived class that inherits from the state class. Represents the Die state of the Enemy FSM
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

typedef  singleton<token> token_state;
typedef  singleton<death> death_state;

typedef  singleton<glob> glob_state;
