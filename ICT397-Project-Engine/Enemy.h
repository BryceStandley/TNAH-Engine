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
	 **/
using namespace luabridge;
class Enemy : public GameObject
{
public:
	float value;
	Enemy(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script, bool first);
	void Print(glm::vec3 p)
	{
		std::cout << "print: " << p.x << " " << p.y << " " << p.z << std::endl;
	}
	~Enemy();

	stateMachine<Enemy>* getFSM()const { return enemyFSM; }

	/**
	*
	* @brief Updates the game object with functionality
	* @param time - the time since the last frame (deltatime)
	*/
	void Update(float time);

	int getHealth() { return health;}

	void decreaseHealth(int health);

	void Render(View lens, float time, Renderer* gameRenderer);

	void SetSate(int num);

	void setAlive(bool a) { alive = a; }
	
	bool killFSM = false;

	int count = 0;

	void SetKillFSM(bool k)
	{
		killFSM = k;
	}

	bool isAlive()
	{
		return alive;
	}

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
	bool handleMessage(const Telegram message)
	{
        if(Debugger::GetInstance()->debugToConsole) std::cout << message.sender << " has sent a message to " << GetId() << " " << message.msg << ", distance: " << DistanceBetween(message.pos) << std::endl;
		if (enemyFSM->handleMessage(message))
		{
			if (DistanceBetween(message.pos) <= 50.0f)
			{
				newPos = message.pos;
				moving = true;
			}
			return true;
		}
		else
			return false;
	}

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

	void ChangeState(std::string state)
	{
		if (state == "wander")
		{
			getFSM()->changeState(&wander_state::getInstance());
		}
		else if (state == "alert")
		{
			getFSM()->changeState(&alert_state::getInstance());
		}
		else if (state == "chase")
		{
			getFSM()->changeState(&chase_state::getInstance());
		}
		else if (state == "flee")
		{
			getFSM()->changeState(&flee_state::getInstance());
		}
		else if (state == "attack")
		{
			getFSM()->changeState(&attack_state::getInstance());
		}
		else if (state == "die")
		{
			getFSM()->changeState(&die_state::getInstance());
		}
		else if (state == "global")
		{
			getFSM()->changeState(&global_state::getInstance());
		}
	}

	bool CheckPrevState(std::string state)
	{
		if (state == "wander")
		{
			return getFSM()->getPreviousState() == &wander_state::getInstance();
		}
		else if (state == "alert")
		{
			return getFSM()->getPreviousState() == &alert_state::getInstance();
		}
		else if (state == "chase")
		{
			return getFSM()->getPreviousState() == &chase_state::getInstance();
		}
		else if (state == "flee")
		{
			return getFSM()->getPreviousState() == &flee_state::getInstance();
		}
		else if (state == "attack")
		{
			return getFSM()->getPreviousState() == &attack_state::getInstance();
		}
		else if (state == "die")
		{
			return getFSM()->getPreviousState() == &die_state::getInstance();
		}
		else if (state == "global")
		{
			return getFSM()->getPreviousState() == &global_state::getInstance();
		}
		else
		{
			return false;
		}
	}
	
	float LookDirection(std::string type)
	{
		if (type == "player")
		{
			return atan2(getVelocity().z, getVelocity().x);
		}
		else
		{
			return atan2(enemyVelocity.z, enemyVelocity.x);
		}
	}

	void SendMessage(int message, std::string type)
	{
		singleton<MessageDispatcher>::getInstance().DisbatchMsgAllOfType(GetId(), message, type);
	}

	bool Kill()
	{
		return !alive;
	}

	void SetMoving(bool m) { moving = m; }
	bool GetMoving() { return moving; }

	glm::vec3 getNewPos() { return newPos; }
	void setNewPos(glm::vec3 p) { newPos = p; }

	glm::vec3 newPos;
	bool moving = false;

	LuaRef wanderLua = NULL;
	LuaRef alert = NULL;
	LuaRef chase = NULL;
	LuaRef fleeLua = NULL;
	LuaRef attack = NULL;
	LuaRef die = NULL;
	LuaRef global = NULL;

private:

	glm::vec3 pPos;
	Model wModel;
	float deltaTime = 0;
	stateMachine<Enemy>* enemyFSM;
	int health;
	int ammo;
	bool alive;
	bool hasWeapon;

	bool token = false;
	bool globalFlag = false;
	bool deathAnim = false;


	int timer = 0;
	int check = 0;	
	float direction = 0.0f;
	double wanderRadius = 0;
	double wanderDistance = 0;
	double wanderJitter = 0;
	glm::vec3 wanderTarget = { 0.0f,0.0f,0.0f };
};

