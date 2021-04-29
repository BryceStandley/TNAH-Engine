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
		token = false;
		std::cout << h << " " << a << std::endl;
	}

	~Enemy()
	{
		delete enemyFSM;
	}

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

	void Render(View lens, float time)
	{
		pPos = lens.GetPosition();
		std::cout << Distance() << std::endl;
		if (alive)
		{
			Model temp = GetModel();
			Shader s = GetShader();
			temp.Render(lens, s, GetPos(), GetRotation(), GetScale(), GetRotate(), time);
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
	float Distance()
	{
		float distance;
		float x = (pPos.x - GetPos().x) * (pPos.x - GetPos().x);
		float y = (pPos.y - GetPos().y) * (pPos.y - GetPos().y);
		float z = (pPos.z - GetPos().z) * (pPos.z - GetPos().z);

		distance = (x + y + z) / 2;

		return distance;
	}

private:
	glm::vec3 pPos;
	stateMachine<Enemy>* enemyFSM;
	int health;
	int ammo;
	bool alive;
	bool token;
};

