#include "Player.h"

Player::Player(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script) : GameObject(p, rot, s, gameRenderer)
{
	lua_State* L = LuaManager::getInstance().getLuaState();

	if (!luaL_dofile(L, script.c_str()))
	{
		LuaRef type = getGlobal(L, "check");
		LuaRef rot = getGlobal(L, "rotate");
		LuaRef mod = getGlobal(L, "model");
		LuaRef vert = getGlobal(L, "vertShader");
		LuaRef frag = getGlobal(L, "fragShader");

		LuaRef xRot = getGlobal(L, "xRotOffset");
		LuaRef yRot = getGlobal(L, "yRotOffset");
		LuaRef zRot = getGlobal(L, "zRotOffset");

		LuaRef yPos = getGlobal(L, "yPosOffset");

		std::string file;
		std::string vertS;
		std::string fragS;
		float xr = 0, yr = 0, zr = 0, yp = 0;
		bool check = false, rotate = false;

		if (type.isBool())
		{
			check = type.cast<bool>();
		}

		if (rot.isBool())
		{
			rotate = rot.cast<bool>();
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

		if (xRot.isNumber())
		{
			xr = xRot.cast<float>();
		}

		if (yRot.isNumber())
		{
			yr = yRot.cast<float>();
		}

		if (zRot.isNumber())
		{
			zr = zRot.cast<float>();
		}

		if (yPos.isNumber())
		{
			yp = yPos.cast<float>();
		}

		Model tempModel(file, gameRenderer, check);
		SetModel(tempModel);

		Shader tempShader(vertS.c_str(), fragS.c_str());
		SetShader(tempShader);

		xRotatioonOffset = xr;
		yRotatioonOffset = yr;
		zRotatioonOffset = zr;

		yPositionOffset = yp;
		SetRotate(rotate);
	}
	else if (!luaL_dofile(L, "./res/scripts/gameobjects/player_default.lua"))
	{
		std::cout << "Player script not found, loading default script" << std::endl;
		LuaRef type = getGlobal(L, "check");
		LuaRef rot = getGlobal(L, "rotate");
		LuaRef mod = getGlobal(L, "model");
		LuaRef vert = getGlobal(L, "vertShader");
		LuaRef frag = getGlobal(L, "fragShader");

		LuaRef xRot = getGlobal(L, "zRotOffset");
		LuaRef yRot = getGlobal(L, "yRotOffset");
		LuaRef zRot = getGlobal(L, "zRotOffset");

		LuaRef yPos = getGlobal(L, "yPosOffset");

		std::string file;
		std::string vertS;
		std::string fragS;
		float xr = 0, yr = 0, zr = 0, yp = 0;
		bool check = false, rotate = false;

		if (type.isBool())
		{
			check = type.cast<bool>();
		}

		if (rot.isBool())
		{
			rotate = rot.cast<bool>();
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

		if (xRot.isNumber())
		{
			xr = xRot.cast<float>();
		}

		if (yRot.isNumber())
		{
			yr = yRot.cast<float>();
		}

		if (zRot.isNumber())
		{
			zr = zRot.cast<float>();
		}

		if (yPos.isNumber())
		{
			yp = yPos.cast<float>();
		}

		Model tempModel(file, gameRenderer, check);
		SetModel(tempModel);

		Shader tempShader(vertS.c_str(), fragS.c_str());
		SetShader(tempShader);

		xRotatioonOffset = xr;
		yRotatioonOffset = yr;
		zRotatioonOffset = zr;

		yPositionOffset = yp;
		SetRotate(rotate);
	}
	else
	{
		std::cout << "ERROR::NO_PLAYER_SCRIPTS_FOUND" << std::endl;
	}

	playerFSM = new stateMachine<Player>(this);
	playerFSM->setCurrentState(&glob_state::getInstance());
	//playerFSM->setGlobalState(&death_state::getInstance());

	SetType("player");
	Update(0.0f);

	if (Debugger::GetInstance()->debugToConsole) std::cout << xRotatioonOffset << " " << yRotatioonOffset << " " << zRotatioonOffset << " " << yPositionOffset << std::endl;
}

void Player::Update(float time)
{

	playerFSM->update();
/*
	if (singleton<Manager>::getInstance().token == "SpeedUp") 
	{
		singleton<Manager>::getInstance().speed = 10;
		increasePoints(50);

	}
		
	else
		singleton<Manager>::getInstance().speed = 5;
	if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "Token = " << singleton<Manager>::getInstance().token << ", Duration = " << singleton<Manager>::getInstance().timer << std::endl;
	*/
}