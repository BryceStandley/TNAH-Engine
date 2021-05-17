#pragma once
#include "singleton.h"
#include "state.h"
#include "Debugger.h"

class Player;


	/**
	* @class doubleDamage
	* @brief A derived class that inherits from the state class. Represents the doubleDamage state of the Player FSM
	*
	* @author Dylan Blereau
	* @version 01
	* @date 02/05/2021 Dylan Blereau, Started
	*
	*
	**/
class doubleDamage :public State<Player>
{
public:

		/**
		* @brief virtual function that represents the entry point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Enter(Player* dude);

		/**
		* @brief virtual function that represents the execute point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Execute(Player* dude);

		/**
		* @brief virtual function that represents the exit point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Exit(Player* dude);
};


	/**
	* @class healthRefill
	* @brief A derived class that inherits from the state class. Represents the healthRefill state of the Player FSM
	*
	* @author Dylan Blereau
	* @version 01
	* @date 02/05/2021 Dylan Blereau, Started
	*
	*
	**/
class healthRefill :public State<Player>
{
public:

		/**
		* @brief virtual function that represents the entry point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Enter(Player* dude);

		/**
		* @brief virtual function that represents the execute point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Execute(Player* dude);

		/**
		* @brief virtual function that represents the exit point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Exit(Player* dude);
};


	/**
	* @class SpeedUp
	* @brief A derived class that inherits from the state class. Represents the SpeedUp state of the Player FSM
	*
	* @author Dylan Blereau
	* @version 01
	* @date 02/05/2021 Dylan Blereau, Started
	*
	*
	**/
class SpeedUp :public State<Player>
{
public:

		/**
		* @brief virtual function that represents the entry point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Enter(Player* dude);

		/**
		* @brief virtual function that represents the execute point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Execute(Player* dude);

		/**
		* @brief virtual function that represents the exit point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Exit(Player* dude);
};


	/**
	* @class doublePoints
	* @brief A derived class that inherits from the state class. Represents the doublePoints state of the Player FSM
	*
	* @author Dylan Blereau
	* @version 01
	* @date 02/05/2021 Dylan Blereau, Started
	*
	*
	**/
class doublePoints :public State<Player>
{
public:

		/**
		* @brief virtual function that represents the entry point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Enter(Player* dude);

		/**
		* @brief virtual function that represents the execute point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Execute(Player* dude);

		/**
		* @brief virtual function that represents the exit point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Exit(Player* dude);
};


	/**
	* @class main
	* @brief A derived class that inherits from the state class. Represents the main state of the Player FSM
	*
	* @author Dylan Blereau
	* @version 01
	* @date 02/05/2021 Dylan Blereau, Started
	*
	*
	**/
class main :public State<Player>
{
public:

		/**
		* @brief virtual function that represents the entry point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Enter(Player* dude);

		/**
		* @brief virtual function that represents the execute point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Execute(Player* dude);

		/**
		* @brief virtual function that represents the exit point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Exit(Player* dude);
};


	/**
	* @class death
	* @brief A derived class that inherits from the state class. Represents the death state of the Player FSM
	*
	* @author Dylan Blereau
	* @version 01
	* @date 02/05/2021 Dylan Blereau, Started
	*
	*
	**/
class death :public State<Player>
{
public:

		/**
		* @brief virtual function that represents the entry point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Enter(Player* dude);

		/**
		* @brief virtual function that represents the execute point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Execute(Player* dude);

		/**
		* @brief virtual function that represents the exit point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Exit(Player* dude);
};


	/**
	* @class glob
	* @brief A derived class that inherits from the state class. Represents the glob (global) state of the Player FSM
	*
	* @author Dylan Blereau
	* @version 01
	* @date 02/05/2021 Dylan Blereau, Started
	*
	*
	**/
class glob :public State<Player>
{
public:

		/**
		* @brief virtual function that represents the entry point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Enter(Player* dude);

		/**
		* @brief virtual function that represents the execute point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Execute(Player* dude);

		/**
		* @brief virtual function that represents the exit point of the state
		* @param dude - a pointer to the Player object
		*/
	virtual void Exit(Player* dude);
};


	/// singletons made for each state ensuring only one instance of each state per FSM 
typedef  singleton<main> main_state;


	/// tokens
typedef  singleton<doubleDamage> damage_state;
typedef  singleton<healthRefill> health_state;
typedef  singleton<SpeedUp> speed_state;
typedef  singleton<doublePoints> points_state;

	/// death
typedef  singleton<death> death_state;


	/// global
typedef  singleton<glob> glob_state;
