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

		if (!luaL_dofile(L, script.c_str()))
		{
			LuaRef type = getGlobal(L, "check");
			LuaRef rot = getGlobal(L, "rotate");

			LuaRef mod = getGlobal(L, "model");
			LuaRef vert = getGlobal(L, "vertShader");
			LuaRef frag = getGlobal(L, "fragShader");
			LuaRef tType = getGlobal(L, "type");

			LuaRef sp = getGlobal(L, "speed");

			std::string file;
			std::string vertS;
			std::string fragS;
			std::string tokType;
			bool check = false, rotate = false;
			float s;

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

			Model tempModel(file, gameRenderer, check);
			SetModel(tempModel);

			Shader tempShader(vertS.c_str(), fragS.c_str());
			SetShader(tempShader);

			SetRotate(rotate);

			tokenType = tokType;
			speed = s;
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

			std::string file;
			std::string vertS;
			std::string fragS;
			std::string tokType;
			bool check = false, rotate = false;
			float s;

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

			Model tempModel(file, gameRenderer, check);
			SetModel(tempModel);

			Shader tempShader(vertS.c_str(), fragS.c_str());
			SetShader(tempShader);

			SetRotate(rotate);

			tokenType = tokType;
			speed = s;
		}
		else
		{
			std::cout << "ERROR::NO_TOKEN_SCRIPTS_FOUND" << std::endl;
		}

		if(Debugger::GetInstance()->debugToConsole) std::cout << "Token speed -> " << speed << std::endl;
	}
		/*
		* @breif Updates the game object with functionality
		* @param time - the time since the last frame (deltatime)
		*/
	void Update(float time);

private:
	std::string tokenType;
	float speed;
};

