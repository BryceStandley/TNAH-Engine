#include "Enemy.h"

Enemy::Enemy(glm::vec3 p, glm::vec3 rot, Renderer* gameRenderer, std::string script) : GameObject(p, rot, 0, gameRenderer)
{
	lua_State* L = LuaManager::getInstance().getLuaState();
	SetScriptName(script);
	int h = 50;
	int a = 5;
	bool living = true, weap = false;
	LuaRef setup = NULL;

	if (!luaL_dofile(L, script.c_str()))
	{
		wanderLua = getGlobal(L, "wander");
		alert = getGlobal(L, "alert");
		chase = getGlobal(L, "chase");
		fleeLua = getGlobal(L, "flee");
		attack = getGlobal(L, "attack");
		die = getGlobal(L, "die");
		global = getGlobal(L, "global");

		setup = getGlobal(L, "setup");
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
		LuaRef acc = getGlobal(L, "accuracy");
		LuaRef dam = getGlobal(L, "damage");

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

		if (acc.isNumber())
		{
			accuracyFactor = acc.cast<float>();
		}

		if (dam.isNumber())
		{
			damage = dam.cast<int>();
		}

		Model tempModel(file, gameRenderer, check, texture, true);
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

			Model tempWeaponModel(weaponModel, gameRenderer, check, weaponTexture, true);
			wModel = tempWeaponModel;
		}
	}
	else if (!luaL_dofile(L, "./res/scripts/gameobjects/enemy_default.lua"))
	{
				wanderLua = getGlobal(L, "wander");
		alert = getGlobal(L, "alert");
		chase = getGlobal(L, "chase");
		fleeLua = getGlobal(L, "flee");
		attack = getGlobal(L, "attack");
		die = getGlobal(L, "die");
		global = getGlobal(L, "global");

		setup = getGlobal(L, "setup");
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
		LuaRef acc = getGlobal(L, "accuracy");
		LuaRef dam = getGlobal(L, "damage");

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

		if (acc.isNumber())
		{
			accuracyFactor = acc.cast<float>();
		}

		if (dam.isNumber())
		{
			damage = dam.cast<int>();
		}

		Model tempModel(file, gameRenderer, check, texture, true);
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

			Model tempWeaponModel(weaponModel, gameRenderer, check, weaponTexture, true);
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
	healthHold = h;
	ammo = a;
	alive = living;
	hasWeapon = weap;
	startTimer = false;
	deathtimer = 2;
	weaponTimer = 0.5f;
	accuracyFactor = 0.35f;
	damage = 10;
	if (setup.isFunction())
	{
		setup(this);
	}
}

Enemy::Enemy(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script, float h, float a, std::string state) : GameObject(p, rot, s, gameRenderer)
{
	lua_State* L = LuaManager::getInstance().getLuaState();
	SetScriptName(script);
	bool living = true, weap = false;
	LuaRef setup = NULL;
	if (!luaL_dofile(L, script.c_str()))
	{
		wanderLua = getGlobal(L, "wander");
		alert = getGlobal(L, "alert");
		chase = getGlobal(L, "chase");
		fleeLua = getGlobal(L, "flee");
		attack = getGlobal(L, "attack");
		die = getGlobal(L, "die");
		global = getGlobal(L, "global");

		setup = getGlobal(L, "setup");
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
		LuaRef acc = getGlobal(L, "accuracy");
		LuaRef dam = getGlobal(L, "damage");

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

		if (acc.isNumber())
		{
			accuracyFactor = acc.cast<float>();
		}

		if (dam.isNumber())
		{
			damage = dam.cast<int>();
		}

		Model tempModel(file, gameRenderer, check, texture, true);
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

			Model tempWeaponModel(weaponModel, gameRenderer, check, weaponTexture, true);
			wModel = tempWeaponModel;
		}
	}
	else if (!luaL_dofile(L, "./res/scripts/gameobjects/enemy_default.lua"))
	{
		wanderLua = getGlobal(L, "wander");
		alert = getGlobal(L, "alert");
		chase = getGlobal(L, "chase");
		fleeLua = getGlobal(L, "flee");
		attack = getGlobal(L, "attack");
		die = getGlobal(L, "die");
		global = getGlobal(L, "global");

		setup = getGlobal(L, "setup");
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
		LuaRef acc = getGlobal(L, "accuracy");
		LuaRef dam = getGlobal(L, "damage");

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

		if (acc.isNumber())
		{
			accuracyFactor = acc.cast<float>();
		}

		if (dam.isNumber())
		{
			damage = dam.cast<int>();
		}

		Model tempModel(file, gameRenderer, check, texture, true);
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

			Model tempWeaponModel(weaponModel, gameRenderer, check, weaponTexture, true);
			wModel = tempWeaponModel;
		}
	}
	else
	{
		std::cout << "ERROR::NO_ENEMY_SCRIPTS_FOUND" << std::endl;
	}
	enemyFSM = new stateMachine<Enemy>(this);
	enemyFSM->setCurrentState(&wander_state::getInstance());
	ChangeState(state);
	enemyFSM->setGlobalState(&global_state::getInstance());
	health = h;
	healthHold = health;
	ammo = a;
	alive = living;
	hasWeapon = weap;
	startTimer = false;
	deathtimer = 2;
	weaponTimer = 0.5f;
	accuracyFactor = 0.35f;
	damage = 10;
	if (setup.isFunction())
	{
		setup(this);
	}
	//Set state
}


Enemy::~Enemy() 
{
    if(Debugger::GetInstance()->debugFSMToConsole)
    {
	    std::cout << "FSM Deleted" << std::endl;
    }
    else if(Debugger::GetInstance()->debugInfoToLogFile)
    {
    	Debugger::GetInstance()->AppendLogger("Enemy.cpp", "Enemy FSM Deleted");
    }
}


void Enemy::Update(float time)
{

	if(Debugger::GetInstance()->debugFSMToConsole)
	{
		std::cout << GetId() << " player has token = " << token << std::endl;
	}
	else if(Debugger::GetInstance()->debugInfoToLogFile)
	{
		Debugger::GetInstance()->AppendLogger("Enemy.cpp", std::to_string(GetId()) +" player has token = " + std::to_string(token));
	}

	//if (function.isTable())
	//{
	//	function[1](this);
	//}
	if (alive)
	{
		if (!startTimer)
		{
			if (singleton<Manager>::getInstance().prevToken == "DoubleDamage" && singleton<Manager>::getInstance().timer >= 0)
			{
				setToken(true);
			}
			else
				setToken(false);

			if (killFSM == false)
				enemyFSM->update();
			else
			{
				if (Debugger::GetInstance()->debugFSMToConsole)
				{
					std::cout << "Should be destroyed" << std::endl;
				}
				else if(Debugger::GetInstance()->debugInfoToLogFile)
				{
					Debugger::GetInstance()->AppendLogger("Enemy.cpp", "Enemy FSM Should be destroyed");
				}
				std::cout << "hi2.1" << std::endl;
				if (getTimer() != 400)
				{
					incrementTimer();
					if (Debugger::GetInstance()->debugToConsole)
					{
						std::cout << "TIMER: " << getTimer() << std::endl;
					}
					else if(Debugger::GetInstance()->debugInfoToLogFile)
					{
						Debugger::GetInstance()->AppendLogger("Enemy.cpp", "Timer: " + std::to_string(getTimer()));
					}
				}
				else if (getTimer() == 400)
				{
					alive = false;
				}
			}

			if(GetModel().GetState().type == 3)
			{
				//If were attacking
				weaponTimer -= time;
				if(weaponTimer <= 0)
				{
					weaponTimer = 0.5f;
					fireWeapon = true;
				}
			}
		}
		else
		{
			deathtimer -= time;
			if (deathtimer <= 0)
				alive = false;
		}
	}
}

void Enemy::decreaseHealth(int health)
{
	this->health -= health;

	if (this->health < 0) 
	{
		this->health = 0;
	}

}

void Enemy::Render(View lens, float time, Renderer* gameRenderer)
{
	pPos = lens.GetPosition();
	deltaTime = time;
    //if(Debugger::GetInstance()->debugFSMToConsole) std::cout << Distance() << std::endl;
	if (alive)
	{
		Model temp = GetModel();
		Shader s = GetShader();
		temp.Render(lens, s, GetPos(), GetRotation(), GetScale(), GetRotate(), time, direction, gameRenderer, false);
		if (hasWeapon)
		{
			wModel.Render(lens, s, GetPos(), GetRotation(), GetScale(), GetRotate(), time, direction, gameRenderer, false);
		}
		SetShader(s);
		SetModel(temp);
	}
}

void Enemy::SetState(int num)
{
	Model temp = GetModel();
	Md2Commands state;
	switch (num)
	{
	case 0:
		state = STAND;
		break;
	case 1:
		state = RUN;
		break;
	case 2:
		state = WALK;
		break;
	case 3:
		state = ATTACK;
		break;
	case 4:
		state = PAIN_A;
		break;
	case 5:
		state = PAIN_B;
		break;
	case 6:
		state = PAIN_C;
		break;
	case 7:
		state = JUMP;
		break;
	case 8:
		state = FLIP;
		break;
	case 9:
		state = SALUTE;
		break;
	case 10:
		state = FALLBACK;
		break;
	case 11:
		state = WAVE;
		break;
	case 12:
		state = POINTING;
		break;
	case 13:
		state = CROUCH_STAND;
		break;
	case 14:
		state = CROUCH_WALK;
		break;
	case 15:
		state = CROUCH_ATTACK;
		break;
	case 16:
		state = CROUCH_PAIN;
		break;
	case 17:
		state = CROUCH_DEATH;
		break;
	case 18:
		state = DEATH_FALLBACK;
		break;
	case 19:
		state = DEATH;
		break;
	case 20:
		state = DEATH_FALLBACKSLOW;
		break;
	default:
		state = WALK;
		break;
	}
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

float Enemy::DistanceBetween(glm::vec3 otherPos)
{
	glm::vec3 oPos = otherPos;
	glm::vec3 modelPos(GetPos().x, GetPos().y, GetPos().z);

	float distance = glm::distance(oPos, modelPos);
	if(Debugger::GetInstance()->debugFSMToConsole)
	{
		std::cout << "Distance: " << distance << " Positions other: " << " " << otherPos.x << " " << otherPos.y << " "
		          << otherPos.z << ", Position enemy: " << modelPos.x << " " << modelPos.y << " " << modelPos.z << " "
		          << std::endl;
	}
	else if(Debugger::GetInstance()->debugInfoToLogFile)
	{
		Debugger::GetInstance()->AppendLogger("Enemy.cpp", "Distance: " + std::to_string(distance) + " Positions other: " + Debugger::GetInstance()->DebugVec3(otherPos) + ", Position enemy: " + Debugger::GetInstance()->DebugVec3(modelPos));
	}

	return distance;
}

bool Enemy::moveTo(glm::vec3& curPos, const glm::vec3& targetPos, glm::vec3& curVelocity, float time, float offset, std::string type)
{
	//calc heading from character position to target
	glm::vec3 target = targetPos - curPos;
	target = glm::normalize(target);

	if (target.x == 0 && target.y == 0 && target.z == 0)
		return true;

	//calc new velocity and new character position
	curVelocity = target * glm::length(curVelocity);
	glm::vec3 displacement = curVelocity * time;
	glm::vec3 vec = curPos + displacement;

	if (type == "Player")
		setVelocity(curVelocity);
	else
		setEnemyVelocity(curVelocity);

	// calculate real target position
	glm::vec3 realTargetPos = targetPos - target * offset;

	// calculate the direction from vec to realTargetPos
	glm::vec3 toRealTarget = realTargetPos - vec;
	toRealTarget = glm::normalize(toRealTarget);

	if (toRealTarget.x == 0 && toRealTarget.y == 0 && toRealTarget.z == 0)
	{
		if(realTargetPos.y < 25.0f)
		{
			curPos = realTargetPos;
		}
		curPos = realTargetPos;
		SetPos(curPos);
		return true;
	}

	//check to see whether vec has gone pass the realTargetPos
	float dp = glm::dot(toRealTarget, target);
	if (dp < 0.0)
	{
		if(realTargetPos.y < 25.0f)
		{
			curPos = realTargetPos;
		}

		SetPos(curPos);
		return true;
	}
	//std::cout << curPos.x << " " << curPos.y << " " << curPos.z << " | " << vec.x << " " << vec.y << " " << vec.z << std::endl;
	// vec has not yet passed realTargetPos
	if(vec.y < 25.0f)
	{
		curPos = vec;
	}

	SetPos(curPos);
	return false;
}

void Enemy::pursue(const glm::vec3& evaderPos, glm::vec3& pursuerPos, const glm::vec3& evaderVelocity, glm::vec3& pursuerVelocity, float time, float offset, std::string type)
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
		moveTo(pursuerPos, evaderPos, pursuerVelocity, time, offset, type);
		//std::cout << "In eyesight" << std::endl;
	}
	else
	{
		lookAheadTime = (glm::length(toEvader)) / (glm::length(evaderVelocity) + glm::length(pursuerVelocity));
		moveTo(pursuerPos, evaderPos + evaderVelocity * (float)lookAheadTime, pursuerVelocity, time, offset, type);
		//std::cout << "outta eyesight" << std::endl;
	}
}

bool Enemy::flee(glm::vec3& curPos, const glm::vec3& pursuerPos, glm::vec3& curVelocity, float fleeSpeed, float time, std::string type)
{
	glm::vec3 fromPursuer = curPos - pursuerPos;

	float panic = 100.0f * 100.0f;

	if (fromPursuer.length() > panic)
		return false;

	fromPursuer = glm::normalize(fromPursuer);
	curVelocity = fromPursuer * fleeSpeed;
	SetPos(curPos + curVelocity * time);
	return true;
}

bool Enemy::evade(glm::vec3& evaderPos, const glm::vec3& pursuerPos, glm::vec3& evaderVelocity, const glm::vec3& pursuerVelocity, float time, std::string type)
{
	//distance between pursuer and evader
	glm::vec3 toPursuer = pursuerPos - evaderPos;

	float lookAheadTime = toPursuer.length() / (evaderVelocity.length() + pursuerVelocity.length());

	return(flee(evaderPos, pursuerPos + pursuerVelocity * lookAheadTime, evaderVelocity, evaderVelocity.length(), time, type));
}

void Enemy::setWander(double wanderRadius, double wanderDistance, double wanderJitter)
{
	this->wanderRadius = wanderRadius;
	this->wanderDistance = wanderDistance;
	this->wanderJitter = wanderJitter;
	double theta = ((rand()) / (RAND_MAX + 1.0)) * (2 * PI);
	wanderTarget = { cos(theta), 0, sin(theta) };
}

bool Enemy::wander(glm::vec3& position, glm::vec3& velocity, float time, std::string type)
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
	moveTo(position, targetWorld, velocity, deltaTime, 0, type);
	return true;
}

void Enemy::ChangeState(std::string state)
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

bool Enemy::CheckPrevState(std::string state)
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

float Enemy::LookDirection(std::string type)
{
	if (type == "player")
	{
		return atan2(getVelocity().z, getVelocity().x);
	}
	else if (type == "playerOpp")
	{
		return atan2(-getVelocity().z, -getVelocity().x);
	}
	else
	{
		return atan2(enemyVelocity.z, enemyVelocity.x);
	}
}

void Enemy::SendMessage(int message, std::string type)
{
	singleton<MessageDispatcher>::getInstance().DisbatchMsgAllOfType(GetId(), message, type);
}

bool Enemy::Kill()
{
	return alive;
}

bool Enemy::handleMessage(const Telegram message)
{
	if (Debugger::GetInstance()->debugToConsole)
	{
		std::cout << message.sender << " has sent a message to " << GetId() << " " << message.msg << ", distance: " << DistanceBetween(message.pos) << std::endl;
	}
	else if(Debugger::GetInstance()->debugInfoToLogFile)
	{
		std::string s;
		s += std::to_string(message.sender) + " has sent a message to " + std::to_string(GetId()) + " " + std::to_string(message.msg) + ", distance: " + std::to_string(DistanceBetween(message.pos));
		Debugger::GetInstance()->AppendLogger("Enemy.cpp", s);
	}


	if (enemyFSM->handleMessage(message))
	{
		if (DistanceBetween(message.pos) <= 1000.0f)
		{
			newPos = message.pos;
			moving = true;
		}
		return true;
	}
	else
		return false;
}

void Enemy::ResetEnemy(glm::vec3 spawn)
{
	SetPos(spawn);
	health = healthHold;
	std::cout << healthHold << std::endl;
	enemyFSM = new stateMachine<Enemy>(this);
	enemyFSM->setCurrentState(&wander_state::getInstance());
	enemyFSM->setGlobalState(&global_state::getInstance());
	SetState(2);
	alive = true;
	startTimer = false;
	deathtimer = 2;
}

std::string Enemy::ReturnState()
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

std::string Enemy::StreamValues()
{
	return GetType() + " " + GetScriptName() + " " + std::to_string(GetScale()) + " " + std::to_string(GetPos().x) + " " + std::to_string(GetPos().y) + " " + std::to_string(GetPos().z) + " " + std::to_string(health) + " " + std::to_string(ammo) + " " + ReturnState() + "\n";
}


std::string Enemy::getDifficulty()
{
	switch (singleton<Manager>::getInstance().difficulty)
	{
	case Manager::Difficulty::hard:
		return "Hard";
	case Manager::Difficulty::normal:
		return "Normal";
	case Manager::Difficulty::easy:
		return "Easy";
	default:
		break;
	}
}