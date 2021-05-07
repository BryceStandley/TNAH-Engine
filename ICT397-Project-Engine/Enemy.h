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
	bool token = true;
	bool deathAnim = false;
	int check = 0;

	stateMachine<Enemy>* getFSM()const { return enemyFSM; }

	/*
	* @breif Updates the game object with functionality
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





	bool moveTo(glm::vec3& curPos, const glm::vec3& targetPos, glm::vec3& curVelocity, float time, float offset);

	void pursue(const glm::vec3& evaderPos, glm::vec3& pursuerPos, const glm::vec3& evaderVelocity, glm::vec3& pursuerVelocity, float time, float offset);
	
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
	//bool token = false;

	double wanderRadius = 0;
	double wanderDistance = 0;
	double wanderJitter = 0;
	glm::vec3 wanderTarget = { 0.0f,0.0f,0.0f };
	
};

