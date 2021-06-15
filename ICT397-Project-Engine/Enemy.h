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
		* @return int health
		*/
	int getHealth() { return health;}


		/**
		* @brief sets the health value for the enemy
		* @param int h
		*/
	void setHealth(int h) { health = h; healthHold = health; }

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

		
	virtual std::string StreamValues();

		/**
		* @brief returns the string value of the state that the FSM is currently in
		* @return std::string
		*/
	std::string ReturnState();

	/**
	 * @brief Gets the accuracy factor of an enemy
	 * @return accuracy factor
	 */
	float GetAccuracy(){return accuracyFactor;}

	/**
	 * @brief Sets the accuracy factor of an enemy
	 * @param a for the accuracy value
	 */
	void SetAccuracy(float a) { accuracyFactor = a; }

	/**
	 * @brief Returns if the enemy is alive or not
	 * @return bool alive
	 */
	bool GetAliveStatus() { return alive; }

	/**
	 * @brief Sets the alive value for the enemy
	 * @param bool s which is then set to alive
	 */
	void SetAliveStatus(bool s) { alive = s; }

	/**
	 * @brief Gets Damage value for the enemy
	 * @return int damage
	 */
	int GetDamage() { return damage; }

	/**
	 * @brief sets Damage value for the enemy
	 * @param int damage
	 */
	void SetDamage(int d) { damage = d; }

	/**
	 * @brief Sets if the weapon is firing or not
	 * @param bool f which is set to fireweapon
	 */
	void SetFireWeapon(bool f) { fireWeapon = f; }

	/**
	 * @brief Gets if the weapon is firing
	 * @return bool fireweapon
	 */
	bool GetFireWeapon() { return fireWeapon; }


	/**
	 * @brief Resets the enemy object, mainly used for pooling so that we dont need to allocate memory for new enemies each time we spawn one, we just reset the one that died
	 * @param vec3 spawn which is used to set the new reset positions of the enemy
	 */
	void ResetEnemy(glm::vec3 spawn);

	/**
	 * @brief returns the current game difficulty as a string
	 * @return string difficulty
	 */
	std::string getDifficulty();

	///the position the enemy is heading too
	glm::vec3 newPos;

	///Wander lua reference
	LuaRef wanderLua = NULL;

	///alert lua reference
	LuaRef alert = NULL;

	///chase lua reference
	LuaRef chase = NULL;

	///flee lua reference
	LuaRef fleeLua = NULL;

	///attack lua reference
	LuaRef attack = NULL;

	///die lua reference
	LuaRef die = NULL;

	///global lua reference
	LuaRef global = NULL;

	///initilise lua reference
	LuaRef init = NULL;

	///Time for when the enemy will despawn
	bool startTimer;

private:

	///The position of the player
	glm::vec3 pPos;

	///The weaponModel
	Model wModel;

	///Delta time
	float deltaTime = 0;

	///The ai state machine for enemy
	stateMachine<Enemy>* enemyFSM;

	///The enemies health
	int health;

	///The held value for health
	int healthHold;

	///The ammo count for enemy
	int ammo;

	///If the enemy is alive
	bool alive;

	///If the enemy has recieved a message
	bool hasWeapon;


	///If the enemy is moving
	bool moving = false;

	///If the player has a token
	bool token = false;

	///If the global flag is true
	bool globalFlag = false;

	///If the global flag 
	bool deathAnim = false;

	///Kill state machine
	bool killFSM = false;


	///Timer
	int timer = 0;

	///Checker
	int check = 0;	

	///Direction it is facing
	float direction = 0.0f;

	///The wander radius
	double wanderRadius = 0;

	///The wander distance
	double wanderDistance = 0;

	///The wander jitter
	double wanderJitter = 0;

	///The wander target
	glm::vec3 wanderTarget = { 0.0f,0.0f,0.0f };

	///The death timer
	float deathtimer;

	///The weapon timer
	float weaponTimer;

	///Fire weapon bool
	bool fireWeapon = false;

	///The accuracy value
	float accuracyFactor;

	///The damage
	int damage;
};

