#include "tnahpch.h"
#include "Static.h"

Static::Static(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script) : GameObject(p, rot, s, gameRenderer)
{
	SetScriptName(script);
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

		tnah::Shader tempShader(vertS.c_str(), fragS.c_str());
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

		tnah::Shader tempShader(vertS.c_str(), fragS.c_str());
		SetShader(tempShader);

		SetRotate(rotate);
	}
	else
	{
		std::cout << "ERROR::NO_STATIC_SCRIPTS_FOUND" << std::endl;
	}
}


void Static::Update(float time)
{
	SetType("static");
}