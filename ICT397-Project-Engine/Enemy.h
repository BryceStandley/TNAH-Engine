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
using namespace luabridge;
class Enemy : public GameObject
{
public:
	Enemy(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script) : GameObject(p, rot, s, gameRenderer)
	{
		lua_State* L = LuaManager::getInstance().getLuaState();

		int h = 50;
		int a = 5;
		bool living = true;

		if (!luaL_dofile(L, script.c_str()))
		{
			LuaRef type = getGlobal(L, "check");
			LuaRef rot = getGlobal(L, "rotate");
			LuaRef alv = getGlobal(L, "alive");

			LuaRef mod = getGlobal(L, "model");
			LuaRef vert = getGlobal(L, "vertShader");
			LuaRef frag = getGlobal(L, "fragShader");

			LuaRef hel = getGlobal(L, "health");
			LuaRef amm = getGlobal(L, "ammo");

			std::string file;
			std::string vertS;
			std::string fragS;
			bool check = false, rotate = false;

			if (type.isBool())
			{
				check = type.cast<bool>();
			}

			if (rot.isBool())
			{
				rotate = rot.cast<bool>();
			}

			if (alv.isBool())
			{
				living = alv.cast<bool>();
			}

			if (mod.isString())
			{
				file = mod.cast<std::string>();
			}

			if (vert.isString())
			{
				vertS = vert.cast<std::string>();
			}

			if (frag.isString())
			{
				fragS = frag.cast<std::string>();
			}

			if (hel.isNumber())
			{
				h = hel.cast<int>();
			}

			if (amm.isNumber())
			{
				a = amm.cast<int>();
			}

			Model tempModel(file, gameRenderer, check);
			SetModel(tempModel);

			Shader tempShader(vertS.c_str(), fragS.c_str());
			SetShader(tempShader);

			SetRotate(rotate);
		}
		else if (!luaL_dofile(L, "./res/scripts/gameobjects/enemy_default.lua"))
		{
			std::cout << "Enemy script not found, loading default script" << std::endl;
			LuaRef type = getGlobal(L, "check");
			LuaRef rot = getGlobal(L, "rotate");
			LuaRef alv = getGlobal(L, "alive");

			LuaRef mod = getGlobal(L, "model");
			LuaRef vert = getGlobal(L, "vertShader");
			LuaRef frag = getGlobal(L, "fragShader");

			LuaRef hel = getGlobal(L, "health");
			LuaRef amm = getGlobal(L, "ammo");

			std::string file;
			std::string vertS;
			std::string fragS;
			bool check = false, rotate = false;

			if (type.isBool())
			{
				check = type.cast<bool>();
			}

			if (rot.isBool())
			{
				rotate = rot.cast<bool>();
			}

			if (alv.isBool())
			{
				living = alv.cast<bool>();
			}

			if (mod.isString())
			{
				file = mod.cast<std::string>();
			}

			if (vert.isString())
			{
				vertS = vert.cast<std::string>();
			}

			if (frag.isString())
			{
				fragS = frag.cast<std::string>();
			}

			if (hel.isNumber())
			{
				h = hel.cast<int>();
			}

			if (amm.isNumber())
			{
				a = amm.cast<int>();
			}

			Model tempModel(file, gameRenderer, check);
			SetModel(tempModel);

			Shader tempShader(vertS.c_str(), fragS.c_str());
			SetShader(tempShader);

			SetRotate(rotate);
		}
		else
		{
			std::cout << "ERROR::NO_ENEMY_SCRIPTS_FOUND" << std::endl;
		}
		enemyFSM = new stateMachine<Enemy>(this);
		enemyFSM->setCurrentState(&wander_state::getInstance());
		enemyFSM->setGlobalState(&global_state::getInstance());
		health = h;
		ammo = a;
		alive = living;
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

