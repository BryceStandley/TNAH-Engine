#pragma once
#include "GameObject.h"
/**
 * @class Static
 * @brief Abstract GameObject class for static game objects
 *
 * @author Christopher Logan
 * @version 01
 * @date 25/03/2021
 *
 *
 * @bugs none to be seen
 *
 **/
using namespace luabridge;
class Static : public GameObject
{
public:
	Static(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script) : GameObject(p, rot, s, gameRenderer)
	{
		lua_State* L = LuaManager::getInstance().getLuaState();

		if (!luaL_dofile(L, script.c_str()))
		{
			LuaRef type = getGlobal(L, "check");
			LuaRef rot = getGlobal(L, "rotate");
			LuaRef mod = getGlobal(L, "model");
			LuaRef vert = getGlobal(L, "vertShader");
			LuaRef frag = getGlobal(L, "fragShader");

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

			Model tempModel(file, gameRenderer, check);
			SetModel(tempModel);

			Shader tempShader(vertS.c_str(), fragS.c_str());
			SetShader(tempShader);

			SetRotate(rotate);
		}
		else if (!luaL_dofile(L, "./res/scripts/gameobjects/static_default.lua"))
		{
			std::cout << "Static script not found, loading default script" << std::endl;
			LuaRef type = getGlobal(L, "check");
			LuaRef rot = getGlobal(L, "rotate");
			LuaRef mod = getGlobal(L, "model");
			LuaRef vert = getGlobal(L, "vertShader");
			LuaRef frag = getGlobal(L, "fragShader");

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

			Model tempModel(file, gameRenderer, check);
			SetModel(tempModel);

			Shader tempShader(vertS.c_str(), fragS.c_str());
			SetShader(tempShader);

			SetRotate(rotate);
		}
		else
		{
			std::cout << "ERROR::NO_STATIC_SCRIPTS_FOUND" << std::endl;
		}
	}
		/**
		* @brief Update function that updates the functionality
		* @param time - the time since the last frame
		*/
	void Update(float time);
};

