#pragma once
#include "GameObject.h"
#include "state.h"
#include "stateMachine.h"
#include "enemyStates.h"
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
class Enemy : public GameObject
{
public:
	Enemy(float h, float a) : GameObject()
	{
		enemyFSM = new stateMachine<Enemy>(this);
		enemyFSM->setCurrentState(&wander_state::getInstance());
		enemyFSM->setGlobalState(&global_state::getInstance());
		health = h;
		ammo = a;
		alive = true;
		
		//std::cout << h << " " << a << std::endl;
	}

	~Enemy()
	{
		delete enemyFSM;
	}

	glm::vec3 velocity;
	float direction = 0.0f;
	bool globalFlag = false;
	bool token = false;
	int check = 0;

	stateMachine<Enemy>* getFSM()const { return enemyFSM; }
	/*
	* @breif Updates the game object with functionality
	* @param time - the time since the last frame (deltatime)
	*/
	void Update(float time);

	void Damage(int dmg)
	{
		health += dmg;

		if (health > 100)
		{
			health = 100;
		}

		if (health <= 0)
		{
			health = 0;
			alive = false;
		}
	}

	void Ammo(int amount)
	{
		ammo += amount;

		if (ammo > 50)
		{
			ammo = 50;
		}

		if (ammo <= 0)
		{
			ammo = 0;
		}
	}

	void Render(View lens, float time, Renderer* gameRenderer)
	{
		pPos = lens.GetPosition();
		deltaTime = time;
		//std::cout << Distance() << std::endl;
		if (alive)
		{
			Model temp = GetModel();
			Shader s = GetShader();
			temp.Render(lens, s, GetPos(), GetRotation(), GetScale(), GetRotate(), time, direction, gameRenderer);
			SetShader(s);
			SetModel(temp);
		}
	}

	void SetSate(Md2Commands state)
	{
		Model temp = GetModel();
		temp.SetState(state);
		SetModel(temp);

	}

	void GetDistance();

	bool hasToken() { return token; }
	bool isAlive() { return alive; }
	bool killFSM = false;

	float GetDeltaTime() const { return deltaTime; }

	float Distance()
	{
		glm::vec3 camPos(pPos.x, pPos.y, pPos.z);
		glm::vec3 modelPos(GetPos().x, GetPos().y, GetPos().z);

		glm::vec3 norm = glm::normalize(camPos - modelPos);

		velocity = (norm * 3.0f);
		
		float distance = glm::distance(camPos, modelPos);

		return distance;
	}

private:
	glm::vec3 pPos;
	
	float deltaTime;
	stateMachine<Enemy>* enemyFSM;
	int health;
	int ammo;
	bool alive;
	//bool token = false;
	
};

