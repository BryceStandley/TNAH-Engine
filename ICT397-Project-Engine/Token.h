#pragma once
#include "GameObject.h"
/**
 * @class Token
 * @brief Abstract GameObject class for in game tokens
 *
 * @author Christopher Logan
 * @version 01
 * @date 25/03/2021
 *
 * @todo add functionality for the tokens
 *
 * @bugs none to be seen
 *
 **/
using namespace luabridge;
class Token : public GameObject
{
public:
	Token(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script) : GameObject(p, rot, s, gameRenderer)
	{
		lua_State* L = LuaManager::getInstance().getLuaState();
		SetScriptName(script);
		if (!luaL_dofile(L, script.c_str()))
		{
			LuaRef type = getGlobal(L, "check");
			LuaRef rot = getGlobal(L, "rotate");

			LuaRef mod = getGlobal(L, "model");
			LuaRef vert = getGlobal(L, "vertShader");
			LuaRef frag = getGlobal(L, "fragShader");
			LuaRef tType = getGlobal(L, "type");

			LuaRef sp = getGlobal(L, "speed");
			LuaRef dur = getGlobal(L, "duration");

			std::string file;
			std::string vertS;
			std::string fragS;
			std::string tokType;
			bool check = false, rotate = false;
			float s = 0, d = 0;

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

			if (tType.isString())
			{
				tokType = tType.cast<std::string>();
			}

			if (sp.isNumber())
			{
				s = sp.cast<float>();
			}

			if (dur.isNumber())
			{
				d = dur.cast<float>();
			}

			Model tempModel(file, gameRenderer, check);
			SetModel(tempModel);

			Shader tempShader(vertS.c_str(), fragS.c_str());
			SetShader(tempShader);

			SetRotate(rotate);

			tokenType = tokType;
			speed = s;
			duration = d;
		}
		else if (!luaL_dofile(L, "./res/scripts/gameobjects/token_default.lua"))
		{
			std::cout << "Token script not found, loading default script" << std::endl;
			LuaRef type = getGlobal(L, "check");
			LuaRef rot = getGlobal(L, "rotate");

			LuaRef mod = getGlobal(L, "model");
			LuaRef vert = getGlobal(L, "vertShader");
			LuaRef frag = getGlobal(L, "fragShader");
			LuaRef tType = getGlobal(L, "type");

			LuaRef sp = getGlobal(L, "speed");
			LuaRef dur = getGlobal(L, "duration");

			std::string file;
			std::string vertS;
			std::string fragS;
			std::string tokType;
			bool check = false, rotate = false;
			float s, d;

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

			if (tType.isString())
			{
				tokType = tType.cast<std::string>();
			}

			if (sp.isNumber())
			{
				s = sp.cast<float>();
			}

			if (dur.isNumber())
			{
				d = dur.cast<float>();
			}

			Model tempModel(file, gameRenderer, check);
			SetModel(tempModel);

			Shader tempShader(vertS.c_str(), fragS.c_str());
			SetShader(tempShader);

			SetRotate(rotate);

			tokenType = tokType;
			speed = s;
			duration = d;
		}
		else
		{
			std::cout << "ERROR::NO_TOKEN_SCRIPTS_FOUND" << std::endl;
		}
		spin = glm::vec3(0, 0, 0);
		if(Debugger::GetInstance()->debugToConsole) std::cout << "Token speed -> " << speed << std::endl;
	}
		/*
		* @breif Updates the game object with functionality
		* @param time - the time since the last frame (deltatime)
		*/
	void Update(float time);
	
	virtual bool Kill()
	{
		std::cout << tokenType << std::endl;
		singleton<Manager>::getInstance().token = tokenType;
		singleton<Manager>::getInstance().timer = duration;
		return false;
	}

	void Render(View lens, float time, Renderer* gameRenderer)
	{
		Model temp = GetModel();
		Shader s = GetShader();
		spin.x += speed * time;
		if (spin.x >= 360)
			spin.x = 0;
		temp.Render(lens, s, GetPos(), spin, GetScale(), GetRotate(), time, 0, gameRenderer, false);
	}

private:
	std::string tokenType;
	float speed;
	float duration;
	glm::vec3 spin;
};

