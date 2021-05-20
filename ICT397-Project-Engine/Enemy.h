#pragma once
# define PI           3.14159265358979323846  /* pi */
#include "state.h"
#include "stateMachine.h"
#include "enemyStates.h"


inline double randFloat()
{
	return ((rand()) / (RAND_MAX + 1.0));
}

inline double randomClamped()
{
	return randFloat() - randFloat();
}


	/**
	 * @class Enemy
	 * @brief Abstract GameObject class for enemies
	 *
	 * @author Christopher Logan
	 * @version 01
	 * @date 25/03/2021
	 *
	 * @todo Add enemy functionality
	 *
	 * @bugs none to be seen
	 *
	 * @author Dylan Blereau
	 * @version 02
	 * @date 05/05/21
	 *
	 * @brief Added enemy FSM and messaging functionality
	 *
	 **/
using namespace luabridge;
class Enemy : public GameObject
{
public:

		/**
		* @brief Enemy constructor that takes various parameters
		* @param p - reperesents the vector position
		* @param rot - represents the rotation vector
		* @param gameRenderer - a pointer to the game engine renderer
		* @param script - a string repesenting the path to the enemy lua script
		*/
	Enemy(glm::vec3 p, glm::vec3 rot, Renderer* gameRenderer, std::string script);

		/**
		* @brief Enemy constructor that takes various parameters
		* @param p - reperesents the vector position
		* @param rot - represents the rotation vector
		* @param s - represents the enemy scale
		* @param gameRenderer - a pointer to the game engine renderer
		* @param script - a string repesenting the path to the enemy lua script
		* @param h - represents the enemy health
		* @param a - represents the enemy ammo
		* @param state - reperesents the enemy state
		*/
	Enemy(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script, float h, float a, std::string state);

		/**
		* @brief Prints the x,y,z values of a given position
		* @param p - reperesents the vector position
		*/
	void Print(glm::vec3 p) 
	{
		std::cout << p.x << " " << p.y << " " << p.z << std::endl;
	}
	
		/**
		* @brief destructor that deallocates resource upon deletion of enemy object
		*/
	~Enemy();

		/**
		* @brief gets and returns the finite state machine of the enemy
		* @return stateMachine<Enemy>*
		*/
	stateMachine<Enemy>* getFSM()const { return enemyFSM; }

		/**
		* @brief Updates the game object with functionality
		* @param time - the time since the last frame (deltatime)
		*/
	void Update(float time);


		/**
		* @brief gets and returns the health value of the enemy
		* @return stateMachine<Enemy>*
		*/
	int getHealth() { return health;}

	/**
	 * @brief Gets the position of the game object
	 * @return pPos - position of the game object
	 */

    glm::vec3 GetPos() const { return GameObject::GetPos(); }
    /**
     * @brief Sets the position of the game object
     * @param p - the glm::vec3 position to be set
     */
    void SetPos(glm::vec3 p) { GameObject::SetPos(p); }

        /**
		* @brief decreases the value of health by the integer provided as a parameter
		* @param health - represents the value that health will be decreased by
		*/
	void decreaseHealth(int health);

		/**
		* @brief makes use of the view information and graphics renderer to render the enemy to the screen
		* @param lens - holds the information that allows you to project and view the model 
		* @param time - represents deltatime, which is the difference between the previous frame and the current frame 
		* @param gameRenderer - a pointer to the renderer which is used to render the enemy model 
		*/
	void Render(View lens, float time, Renderer* gameRenderer);

		/**
		* @brief sets the animation state to the value provided as parameter, whether it be an integer or an enumerated type
		* @param num - represents the num or enum that belongs to an animation state
		*/
	void SetState(int num);

		/**
		* @brief sets the boolean value of the alive variable
		* @param a - represents the value that will be assigned to the alive boolean variable
		*/
	void setAlive(bool a) { alive = a; }
	
		/**
		* @brief sets the boolean value of the killFSM variable
		* @param k - represents the value that will be assigned to the killFSM boolean variable
		*/
	void SetKillFSM(bool k) 
	{
		killFSM = k;
	};

		/**
		* @brief gets and returns the alive boolean value
		* @return bool
		*/
	bool isAlive() { return alive; };
	
		/**
		* @brief gets and returns the value of deletaTime
		* @return float
		*/
	float GetDeltaTime() const { return deltaTime; }

		/**
		* @brief gets and returns the distance between the enemy and the first person player camera
		* @return float
		*/
	float Distance();


		/**
		* @brief gets and returns the distance between a given position and an enemy position  
		* @return float
		*/
	float DistanceBetween(glm::vec3 otherPos);
	

		/**
		* @brief gets and returns the position of the first person player camera
		* @return glm::vec3
		*/
	glm::vec3 getCamPos() { return pPos; }
	
	/// enemyVelocity
	glm::vec3 enemyVelocity = { 6.0f, 0.0f, 0.0f };

	/// cam Velocity
	glm::vec3 velocity = { 4.0f, 0.0f, 0.0f };

		/**
		* @brief allows the enemy to handle messages it receives from other entities
		* @param message - represents the message sent to the enemy
		* @return bool
		*/
	bool handleMessage(const Telegram message);

		/**
		* @brief allows the enemy to move from its current position to a specified target position
		* @param curPos - the vector representing the current position of the enemy
		* @param targetPos - the vector representing the target position to move to
		* @param curVelocity - represents the enemy's current velocity
		* @param time - represents the time used to calculate the displacement
		* @param offset - the distance that the character should maintain between itself and its target
		* @return bool
		*/
	bool moveTo(glm::vec3& curPos, const glm::vec3& targetPos, glm::vec3& curVelocity, float time, float offset, std::string type);

		/**
		* @brief allows the enemy to pursue an evading target
		* @param evaderPos - the vector representing the position of the evader (the first-person camera)
		* @param pursuerPos - the vector representing the position of the pursuer (the enemy)
		* @param evaderVelocity - represents the velocity of the evader
		* @param pursuerVelocity - represent the velocity of the pursuer
		* @param time - represents the time used to calculate the displacement
		* @param offset - the distance that the enemy should maintain between itself and its target
		*/
	void pursue(const glm::vec3& evaderPos, glm::vec3& pursuerPos, const glm::vec3& evaderVelocity, glm::vec3& pursuerVelocity, float time, float offset, std::string type);
	
		/**
		* @brief allows the enemy to flee from a pursuing entity
		* @param curPos - the vector representing the current position of the enemy
		* @param pursuerPos - the vector representing the position of the pursuer
		* @param curVelocity - represent the velocity of the pursuer
		* @param fleeSpeed - represents the fleeSpeed that is used to set the velocity
		* @param time - represents the time that is multiplied by velocity to update the current position
		* @return bool
		*/
	bool flee(glm::vec3& curPos, const glm::vec3& pursuerPos, glm::vec3& curVelocity, float fleeSpeed, float time, std::string type);

		/**
		* @brief allows the enemy to evade a pursuing entity. Serves as a flee that moves from the predicted future position of the pursuer
		* @param evaderPos - the vector representing the current position of the enemy
		* @param pursuerPos - the vector representing the position of the pursuer
		* @param evaderVelocity - represents the velocity of the evader
		* @param pursuerVelocity - represents the velocity of the pursuer
		* @param time - represents the time
		* @return bool
		*/
	bool evade(glm::vec3& evaderPos, const glm::vec3& pursuerPos, glm::vec3& evaderVelocity, const glm::vec3& pursuerVelocity, float time, std::string type);

		/**
		* @brief a function used to set the values that will be used in the wander movement function
		* @param wanderRadius - the radius of the wander circle
		* @param wanderDistance - the distance the wander circle is projected in front of the agent
		* @param wanderJitter - represents the max amount of the displacement
		*/
	void setWander(double wanderRadius, double wanderDistance, double wanderJitter);

		/**
		* @brief a function used to set the values that will be used in the wander movement function
		* @param position - the position of the enemy
		* @param velocity - the velocity of the enemy
		* @param time - represents the time
		* @return bool
		*/
	bool wander(glm::vec3& position, glm::vec3& velocity, float time, std::string type);

		/**
		* @brief gets and returns the velocity vector
		* @return glm::vec3
		*/
	glm::vec3 getVelocity() const { return velocity; }

		/**
		* @brief function that allows you to set the values of the velocity vector
		* @param v - represents the vector value you want to assign to velocity
		*/
	void setVelocity(glm::vec3 v) { velocity = v;}

		/**
		* @brief gets and returns the enemy velocity vector
		* @return glm::vec3
		*/
	glm::vec3 getEnemyVelocity() const { return enemyVelocity; }

		/**
		* @brief function that allows you to set the values of the enemyVelocity vector
		* @param v - represents the vector value you want to assign to enemyVelocity
		*/
	void setEnemyVelocity(glm::vec3 v) { enemyVelocity = v; }

		/**
		* @brief gets and returns the direction in which the enemy is facing
		* @return float
		*/
	float getDirection() const { return direction; }

		/**
		* @brief sets the direction in which the enemy is facing
		* @param dir - reprsents the direction value you want to set
		*/
	void setDirection(float dir) { direction = dir;}

		/**
		* @brief gets and returns the value of the globalFlag (globalFlag is used to ensure that globalState changes don't get stuck in a loop)
		* @return bool
		*/
	bool getGlobalFlag() const { return globalFlag; }

		/**
		* @brief sets the value of the globalFlag
		* @param flag - represents the value you want to set globalFlag 
		*/
	void setGlobalFlag(bool flag) { globalFlag = flag; }

		/**
		* @brief gets and returns the value of the token
		* @return bool
		*/
	bool getToken() const { return token; }

		/**
		* @brief sets the value of the token
		* @param t - represents the value you want to set token
		*/
	void setToken(bool t) { token = t; }

		/**
		* @brief gets and returns the value of the deathAnim flag
		* @return bool
		*/
	bool getDeathAnim() const { return deathAnim; }

		/**
		* @brief sets the value of the deathAnim boolean
		* @param d - represents the value you want to set deathAnim
		*/
	void setDeathAnim(bool d) { deathAnim = d; }

		/**
		* @brief gets and returns the value of the timer
		* @return int
		*/
	int getTimer() const { return timer; }

		/**
		* @brief sets the value of the timer
		* @param t - represents the value you want to assign the timer
		*/
	void setTimer(int t) { timer = t; }

		/**
		* @brief increments the timer value
		* @return int
		*/
	int incrementTimer() { return timer++; }

		/**
		* @brief gets and returns the value of the check
		* @return int
		*/
	int getCheck() const { return check; }

		/**
		* @brief sets the value of the check
		* @param c - represents the value you want to assign the check
		*/
	void setCheck(int c) { check = c; }

		/**
		* @brief increments the check value
		* @return int
		*/
	int incrementCheck() { return check++; }

		/**
		* @brief a function that changes the enemy state to the state provided to the function provided as a parameter
		* @param state - represents the state that the fsm will change to
		* @return bool
		*/
	void ChangeState(std::string state);

		/**
		* @brief a function that returns the previous state so long as the state parameter provided matches a valid state, otherwise it returns false
		* @param state - represents the state that the fsm will check to see if its the previous state
		* @return bool
		*/
	bool CheckPrevState(std::string state);
	
		/**
		* @brief a function that returns the looking direction of the enemy dependant on which string is provided
		* @param type - represents the type of thing that should be looked at (which in this case in the enemy looking at the player)
		* @return float
		*/
	float LookDirection(std::string type);

		/**
		* @brief a function that will send a message from the enemy to a specified gameObject type
		* @param message - refers to the message being sent
		* @param type - refers to the type of gameobject the message is being sent to
		*/
	void SendMessage(int message, std::string type);

		/**
		* @brief sets the value of the moving boolean value, which is set to true when the enemy is moving towards the enemy that has seen the player and called for their help
		* @param m - represents the value you want to assign the moving boolean
		*/
	void SetMoving(bool m) { moving = m; }

		/**
		* @brief gets and returns the value of moving
		* @return bool
		*/
	bool GetMoving() { return moving; }

		/**
		* @brief gets and returns the the newPos vector
		* @return glm::vec3
		*/
	glm::vec3 getNewPos() { return newPos; }

		/**
		* @brief sets the value of the newPos vector
		* @param p - represents the value you want to assign the newPos vector
		*/
	void setNewPos(glm::vec3 p) { newPos = p; }
	
		/**
		* @brief returns the killFSM bool value
		* @return bool
		*/
	bool Kill();

		
	virtual std::string StreamValues()
	{
		return GetType() + " " + GetScriptName() + " " + std::to_string(GetScale()) + " " + std::to_string(GetPos().x) + " " + std::to_string(GetPos().y) + " " + std::to_string(GetPos().z) + " " + std::to_string(health) + " " + std::to_string(ammo) +  " " + ReturnState() + "\n";
	}

		/**
		* @brief returns the string value of the state that the FSM is currently in
		* @return std::string
		*/
	std::string ReturnState()
	{
		if (getFSM()->getCurrentState() == &global_state::getInstance())
		{
			return "global";
		}
		else if (getFSM()->getCurrentState() == &wander_state::getInstance())
		{
			return "wander";
		}
		else if (getFSM()->getCurrentState() == &chase_state::getInstance())
		{
			return "chase";
		}
		else if (getFSM()->getCurrentState() == &flee_state::getInstance())
		{
			return "flee";
		}
		else if (getFSM()->getCurrentState() == &alert_state::getInstance())
		{
			return "alert";
		}
		else if (getFSM()->getCurrentState() == &die_state::getInstance())
		{
			return "die";
		}
		else if (getFSM()->getCurrentState() == &attack_state::getInstance())
		{
			return "attack";
		}
		else
		{
			return "";
		}
	}

	glm::vec3 newPos;
	LuaRef wanderLua = NULL;
	LuaRef alert = NULL;
	LuaRef chase = NULL;
	LuaRef fleeLua = NULL;
	LuaRef attack = NULL;
	LuaRef die = NULL;
	LuaRef global = NULL;
	LuaRef init = NULL;

	std::string getDifficulty()
	{
		switch (singleton<Manager>::getInstance().difficulty)
		{
		case hard:
			return "Hard";
		case normal:
			return "Normal";
		case easy:
			return "Easy";
		default:
			break;
		}
	}



private:

	glm::vec3 pPos;
	Model wModel;
	float deltaTime = 0;
	stateMachine<Enemy>* enemyFSM;
	int health;
	int ammo;
	bool alive;
	bool hasWeapon;

	bool moving = false;
	bool token = false;
	bool globalFlag = false;
	bool deathAnim = false;
	bool killFSM = false;

	int timer = 0;
	int check = 0;	
	float direction = 0.0f;
	double wanderRadius = 0;
	double wanderDistance = 0;
	double wanderJitter = 0;
	glm::vec3 wanderTarget = { 0.0f,0.0f,0.0f };
};

