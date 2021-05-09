#pragma once
#include "singleton.h"
#include "state.h"

class Enemy;


	/**
	* @class wander
	* @brief A derived class that inherits from the state class. Represents the Wander state of the Enemy FSM
	*
	* @author Dylan Blereau
	* @version 01
	* @date 27/04/2021 Dylan Blereau, Started
	*
	*
	**/
class wander :public State<Enemy>
{
public:

		/**
		* @brief virtual function that represents the entry point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Enter(Enemy* dude);

		/**
		* @brief virtual function that represents the execute point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Execute(Enemy* dude);

		/**
		* @brief virtual function that represents the exit point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Exit(Enemy* dude);
};

	/**
	* @class alert
	* @brief A derived class that inherits from the state class. Represents the Die state of the Enemy FSM
	*
	* @author Dylan Blereau
	* @version 01
	* @date 27/04/2021 Dylan Blereau, Started
	*
	*
	**/
class alert :public State<Enemy>
{
public:

		/**
		* @brief virtual function that represents the entry point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Enter(Enemy* dude);

		/**
		* @brief virtual function that represents the execute point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Execute(Enemy* dude);

		/**
		* @brief virtual function that represents the exit point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Exit(Enemy* dude);
};

class chase : public State<Enemy>
{
public:
	virtual void Enter(Enemy* dude);
	virtual void Execute(Enemy* dude);
	virtual void Exit(Enemy* dude);
};

	/**
	* @class flee
	* @brief A derived class that inherits from the state class. Represents the Flee state of the Enemy FSM
	*
	* @author Dylan Blereau
	* @version 01
	* @date 27/04/2021 Dylan Blereau, Started
	*
	*
	**/
class flee :public State<Enemy>
{
public:

		/**
		* @brief virtual function that represents the entry point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Enter(Enemy* dude);

		/**
		* @brief virtual function that represents the execute point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Execute(Enemy* dude);

		/**
		* @brief virtual function that represents the exit point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Exit(Enemy* dude);
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
class attack :public State<Enemy>
{
public:

		/**
		* @brief virtual function that represents the entry point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Enter(Enemy* dude);

		/**
		* @brief virtual function that represents the execute point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Execute(Enemy* dude);

		/**
		* @brief virtual function that represents the exit point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Exit(Enemy* dude);
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
class die :public State<Enemy>
{
public:

		/**
		* @brief virtual function that represents the entry point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Enter(Enemy* dude);

		/**
		* @brief virtual function that represents the execute point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Execute(Enemy* dude);

		/**
		* @brief virtual function that represents the exit point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Exit(Enemy* dude);
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
class global :public State<Enemy>
{
public:

		/**
		* @brief virtual function that represents the entry point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Enter(Enemy* dude);

		/**
		* @brief virtual function that represents the execute point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Execute(Enemy* dude);

		/**
		* @brief virtual function that represents the exit point of the state
		* @param dude - a pointer to the Enemy object
		*/
	virtual void Exit(Enemy* dude);
};


/// singletons made for each state ensuring only one instance of each state per FSM 
typedef  singleton<wander> wander_state;
typedef  singleton<alert> alert_state;
typedef  singleton<chase> chase_state;
typedef  singleton<flee> flee_state;
typedef  singleton<attack> attack_state;
typedef  singleton<die> die_state;

typedef  singleton<global> global_state;

