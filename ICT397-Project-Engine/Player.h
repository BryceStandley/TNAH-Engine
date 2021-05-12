#pragma once
#include "GameObject.h"
#include "Manager.h"
#include "singleton.h"
/**
 * @class Player
 * @brief Abstract GameObject class for the player
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
class Player : public GameObject
{
public:
		/*
		* @breif Default constructor
		*/
	Player(glm::vec3 p, glm::vec3 rot, float s, Renderer * gameRenderer, std::string script) : GameObject(p, rot, s, gameRenderer)
	{ 
		lua_State* L = LuaManager::getInstance().getLuaState();

		if(!luaL_dofile(L, script.c_str()))
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

		SetType("player");
		Update(0.0f);

        if(Debugger::GetInstance()->debugToConsole) std::cout << xRotatioonOffset << " " << yRotatioonOffset << " " << zRotatioonOffset << " " << yPositionOffset << std::endl;
	}

		/*
		* @breif Updates the game object with functionality
		* @param time - the time since the last frame (deltatime)
		*/
	void Update(float time);

	virtual void Render(View lens, float time, Renderer* gameRenderer)
	{
		glm::vec3 pos = lens.GetPosition();
		pos.y += yPositionOffset;
		SetRotation(glm::vec3(xRotatioonOffset + lens.GetRotation().x * -1, yRotatioonOffset + lens.GetRotation().y * -1, lens.GetRotation().z + zRotatioonOffset));
		Model temp = GetModel();
		Shader s = GetShader();
		temp.Render(lens, s, pos, GetRotation(), GetScale(), GetRotate(), time, 0, gameRenderer);
		SetShader(s);
		SetModel(temp);
	}

private:

	float xRotatioonOffset;
	float yRotatioonOffset;
	float zRotatioonOffset;
	float yPositionOffset;
};

