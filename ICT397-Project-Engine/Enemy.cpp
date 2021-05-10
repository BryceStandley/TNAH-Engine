#include "Enemy.h"

Enemy::Enemy(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script) : GameObject(p, rot, s, gameRenderer)
{
	lua_State* L = LuaManager::getInstance().getLuaState();

	int h = 50;
	int a = 5;
	bool living = true, weap = false;

	if (!luaL_dofile(L, script.c_str()))
	{
		LuaRef type = getGlobal(L, "check");
		LuaRef rot = getGlobal(L, "rotate");
		LuaRef alv = getGlobal(L, "alive");
		LuaRef weapon = getGlobal(L, "weapon");

		LuaRef mod = getGlobal(L, "model");
		LuaRef tex = getGlobal(L, "texture");
		LuaRef vert = getGlobal(L, "vertShader");
		LuaRef frag = getGlobal(L, "fragShader");

		LuaRef hel = getGlobal(L, "health");
		LuaRef amm = getGlobal(L, "ammo");

		std::string file;
		std::string vertS;
		std::string fragS;
		std::string texture;
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

		if (weapon.isBool())
		{
			weap = weapon.cast<bool>();
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

		if (tex.isString())
		{
			texture = tex.cast<std::string>();
		}

		if (hel.isNumber())
		{
			h = hel.cast<int>();
		}

		if (amm.isNumber())
		{
			a = amm.cast<int>();
		}

		Model tempModel(file, gameRenderer, check, texture);
		SetModel(tempModel);

		Shader tempShader(vertS.c_str(), fragS.c_str());
		SetShader(tempShader);

		SetRotate(rotate);

		if (weap)
		{
			LuaRef WeapMod = getGlobal(L, "weaponModel");
			LuaRef weapTex = getGlobal(L, "weaponTexture");

			std::string weaponModel;
			std::string weaponTexture;

			if (WeapMod.isString())
			{
				weaponModel = WeapMod.cast<std::string>();
			}

			if (weapTex.isString())
			{
				weaponTexture = weapTex.cast<std::string>();
			}

			Model tempWeaponModel(weaponModel, gameRenderer, check, weaponTexture);
			wModel = tempWeaponModel;
		}
	}
	else if (!luaL_dofile(L, "./res/scripts/gameobjects/enemy_default.lua"))
	{
		std::cout << "Enemy script not found, loading default script" << std::endl;
		LuaRef type = getGlobal(L, "check");
		LuaRef rot = getGlobal(L, "rotate");
		LuaRef alv = getGlobal(L, "alive");
		LuaRef weapon = getGlobal(L, "weapon");

		LuaRef mod = getGlobal(L, "model");
		LuaRef tex = getGlobal(L, "texture");
		LuaRef vert = getGlobal(L, "vertShader");
		LuaRef frag = getGlobal(L, "fragShader");

		LuaRef hel = getGlobal(L, "health");
		LuaRef amm = getGlobal(L, "ammo");

		std::string file;
		std::string vertS;
		std::string fragS;
		std::string texture;
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

		if (weapon.isBool())
		{
			weap = weapon.cast<bool>();
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

		if (tex.isString())
		{
			texture = tex.cast<std::string>();
		}

		if (hel.isNumber())
		{
			h = hel.cast<int>();
		}

		if (amm.isNumber())
		{
			a = amm.cast<int>();
		}

		Model tempModel(file, gameRenderer, check, texture);
		SetModel(tempModel);

		Shader tempShader(vertS.c_str(), fragS.c_str());
		SetShader(tempShader);

		SetRotate(rotate);

		if (weap)
		{
			LuaRef WeapMod = getGlobal(L, "weaponModel");
			LuaRef weapTex = getGlobal(L, "weaponTexture");

			std::string weaponModel;
			std::string weaponTexture;

			if (WeapMod.isString())
			{
				weaponModel = WeapMod.cast<std::string>();
			}

			if (weapTex.isString())
			{
				weaponTexture = weapTex.cast<std::string>();
			}

			Model tempWeaponModel(weaponModel, gameRenderer, check, weaponTexture);
			wModel = tempWeaponModel;
		}
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
	hasWeapon = weap;
}


Enemy::~Enemy() 
{
	std::cout << "FSM Deleted" << std::endl;
}


void Enemy::Update(float time)
{
	SetType("enemy");

	//std::cout << GetId() << " player has token = " << token << std::endl;

	if (killFSM == false)
		enemyFSM->update();
	else 
	{
		std::cout << "Should be destroyed" << std::endl;
	}
}

void Enemy::Damage(int dmg) 
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

void Enemy::Ammo(int amount) 
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

void Enemy::Render(View lens, float time, Renderer* gameRenderer)
{
	pPos = lens.GetPosition();
	deltaTime = time;
	//std::cout << Distance() << std::endl;
	if (alive)
	{
		Model temp = GetModel();
		Shader s = GetShader();
		temp.Render(lens, s, GetPos(), GetRotation(), GetScale(), GetRotate(), time, direction, gameRenderer);
		if (hasWeapon)
		{
			wModel.Render(lens, s, GetPos(), GetRotation(), GetScale(), GetRotate(), time, direction, gameRenderer);
		}
		SetShader(s);
		SetModel(temp);
	}
}

void Enemy::SetSate(Md2Commands state)
{
	Model temp = GetModel();
	temp.SetState(state);
	SetModel(temp);
	wModel.SetState(state);
}

float Enemy::Distance()
{
	glm::vec3 camPos(pPos.x, pPos.y, pPos.z);
	glm::vec3 modelPos(GetPos().x, GetPos().y, GetPos().z);

	glm::vec3 norm = glm::normalize(camPos - modelPos);

	velocity = (norm * 3.0f);

	float distance = glm::distance(camPos, modelPos);

	return distance;
}

bool Enemy::moveTo(glm::vec3& curPos, const glm::vec3& targetPos, glm::vec3& curVelocity, float time, float offset)
{
	//calc heading from character position to target
	glm::vec3 target = targetPos - curPos;
	target = glm::normalize(target);

	if (target.x == 0 && target.y == 0 && target.z == 0)
		return true;

	//calc new velocity and new character position
	curVelocity = target * glm::length(curVelocity);
	glm::vec3 displacement = curVelocity * time;
	glm::vec3 newPos = curPos + displacement;

	// calculate real target position
	glm::vec3 realTargetPos = targetPos - target * offset;

	// calculate the direction from newPos to realTargetPos
	glm::vec3 toRealTarget = realTargetPos - newPos;
	toRealTarget = glm::normalize(toRealTarget);

	if (toRealTarget.x == 0 && toRealTarget.y == 0 && toRealTarget.z)
	{
		curPos = realTargetPos;
		return true;
	}

	//check to see whether newPos has gone pass the realTargetPos
	float dp = glm::dot(toRealTarget, target);
	if (dp < 0.0)
	{
		curPos = realTargetPos;
		return true;
	}

	// newPos has not yet passed realTargetPos
	curPos = newPos;
	return false;
}

void Enemy::pursue(const glm::vec3& evaderPos, glm::vec3& pursuerPos, const glm::vec3& evaderVelocity, glm::vec3& pursuerVelocity, float time, float offset)
{
	double lookAheadTime;

	//distance between evader and pursuer
	glm::vec3 toEvader = evaderPos - pursuerPos;

	//compute two agents headings
	glm::vec3 pursuerHeading = pursuerVelocity;
	pursuerHeading = glm::normalize(pursuerHeading);

	glm::vec3 evaderHeading = evaderVelocity;
	evaderHeading = glm::normalize(evaderHeading);

	//compute angle between two agents 
	double relativeHeading = glm::dot(pursuerHeading, evaderHeading);

	//std::cout << "relativeHeading = " << relativeHeading << std::endl;

	//std::cout << "Evader Velocity Length:  " << glm::length(evaderVelocity) << std::endl;

	//determine if evader is facing pursuer
	if ((relativeHeading < -0.95) || glm::length(evaderVelocity) == 1)
	{
		moveTo(pursuerPos, evaderPos, pursuerVelocity, time, offset);
		//std::cout << "In eyesight" << std::endl;
	}
	else
	{
		lookAheadTime = (glm::length(toEvader)) / (glm::length(evaderVelocity) + glm::length(pursuerVelocity));
		moveTo(pursuerPos, evaderPos + evaderVelocity * (float)lookAheadTime, pursuerVelocity, time, offset);
		//std::cout << "outta eyesight" << std::endl;
	}
}

bool Enemy::flee(glm::vec3& curPos, const glm::vec3& pursuerPos, glm::vec3& curVelocity, float fleeSpeed, float time)
{
	glm::vec3 fromPursuer = curPos - pursuerPos;

	float panic = 100.0f * 100.0f;

	if (fromPursuer.length() > panic)
		return false;

	fromPursuer = glm::normalize(fromPursuer);
	curVelocity = fromPursuer * fleeSpeed;
	curPos += curVelocity * time;
	return true;
}

bool Enemy::evade(glm::vec3& evaderPos, const glm::vec3& pursuerPos, glm::vec3& evaderVelocity, const glm::vec3& pursuerVelocity, float time)
{
	//distance between pursuer and evader
	glm::vec3 toPursuer = pursuerPos - evaderPos;

	float lookAheadTime = toPursuer.length() / (evaderVelocity.length() + pursuerVelocity.length());

	return(flee(evaderPos, pursuerPos + pursuerVelocity * lookAheadTime, evaderVelocity, evaderVelocity.length(), time));
}

void Enemy::setWander(double wanderRadius, double wanderDistance, double wanderJitter)
{
	this->wanderRadius = wanderRadius;
	this->wanderDistance = wanderDistance;
	this->wanderJitter = wanderJitter;
	double theta = ((rand()) / (RAND_MAX + 1.0)) * (2 * PI);
	wanderTarget = { cos(theta), 0, sin(theta) };
}

bool Enemy::wander(glm::vec3& position, glm::vec3& velocity, float time)
{
	float jitter = wanderJitter * time;

	wanderTarget += glm::vec3(randomClamped() * jitter, 0.0, randomClamped() * jitter);

	//reproject the new vector back on to a unit circle
	wanderTarget = glm::normalize(wanderTarget);

	glm::vec3 heading(velocity);
	heading = glm::normalize(heading);

	glm::vec3 wanderCircleWorldCentre = position + (heading * (float)wanderDistance);

	//project the wanderTarget to the enlarged wander circle in the world
	glm::vec3 targetWorld = wanderCircleWorldCentre + (wanderTarget * (float)wanderRadius);

	//move to the new target position
	moveTo(position, targetWorld, velocity, deltaTime, 0);
	return true;
}


