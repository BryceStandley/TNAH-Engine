#pragma once
# define PI           3.14159265358979323846  /* pi */
#include "GameObject.h"
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

	Enemy(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script);
		
	~Enemy();

	glm::vec3 velocity = { 4.0f, 0.0f, 0.0f };
	glm::vec3 enemyVelocity = { 5.0f, 0.0f, 0.0f };
	float direction = 0.0f;
	bool globalFlag = false;
	bool token = false;
	bool deathAnim = false;
	int timer = 0;
	int check = 0;

	stateMachine<Enemy>* getFSM()const { return enemyFSM; }

	/**
	* @brief Updates the game object with functionality
	* @param time - the time since the last frame (deltatime)
	*/
	void Update(float time);

	void Damage(int dmg);
	

	void Ammo(int amount);
	

	void Render(View lens, float time, Renderer* gameRenderer);

	void SetSate(Md2Commands state);

	bool hasToken() { return token; }
	bool isAlive() { return alive; }
	
	bool killFSM = false;

	float GetDeltaTime() const { return deltaTime; }

	float Distance();
	
	glm::vec3 getCamPos() { return pPos; }




		/**
		* @brief allows the enemy to move from its current position to a specified target position
		* @param curPos - the vector representing the current position of the enemy
		* @param targetPos - the vector representing the target position to move to
		* @param curVelocity - represents the enemy's current velocity
		* @param time - represents the time used to calculate the displacement
		* @param offset - the distance that the character should maintain between itself and its target
		* @return bool
		*/
	bool moveTo(glm::vec3& curPos, const glm::vec3& targetPos, glm::vec3& curVelocity, float time, float offset);

		/**
		* @brief allows the enemy to pursuer an evading target
		* @param evaderPos - the vector representing the position of the evader (the first-person camera)
		* @param pursuerPos - the vector representing the position of the pursuer (the enemy)
		* @param evaderVelocity - represents the velocity of the evader
		* @param pursuerVelocity - represent the velocity of the pursuer
		* @param time - represents the time used to calculate the displacement
		* @param offset - the distance that the enemy should maintain between itself and its target
		*/
	void pursue(const glm::vec3& evaderPos, glm::vec3& pursuerPos, const glm::vec3& evaderVelocity, glm::vec3& pursuerVelocity, float time, float offset);
	

		/**
		* @brief allows the enemy to flee from a pursuing entity
		* @param curPos - the vector representing the current position of the enemy
		* @param pursuerPos - the vector representing the position of the pursuer
		* @param curVelocity - represent the velocity of the pursuer
		* @param fleeSpeed - represents the fleeSpeed that is used to set the velocity
		* @param time - represents the time that is multiplied by velocity to update the current position
		* @return bool
		*/
	bool flee(glm::vec3& curPos, const glm::vec3& pursuerPos, glm::vec3& curVelocity, float fleeSpeed, float time);


	bool evade(glm::vec3& evaderPos, const glm::vec3& pursuerPos, glm::vec3& evaderVelocity, const glm::vec3& pursuerVelocity, float time);

	void setWander(double wanderRadius, double wanderDistance, double wanderJitter);

	bool wander(glm::vec3& position, glm::vec3& velocity, float time);

private:
	glm::vec3 pPos;
	Model wModel;
	float deltaTime = 0;
	stateMachine<Enemy>* enemyFSM;
	int health;
	int ammo;
	bool alive;
	bool hasWeapon;

	double wanderRadius = 0;
	double wanderDistance = 0;
	double wanderJitter = 0;
	glm::vec3 wanderTarget = { 0.0f,0.0f,0.0f };
	
};

