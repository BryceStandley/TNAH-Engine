#include "Input.h"

Input::Input()
{
	lua_State* L = LuaManager::getInstance().getLuaState();

	if (luaL_dofile(L, "./res/scripts/input.lua"))
	{
		std::cout << "ERROR::INPUT_LUA::FILE_WAS_NOT_FOUND::DEFAULT_INPUT" << std::endl;
		foward = GLFW_KEY_W;
		back = GLFW_KEY_S;
		left = GLFW_KEY_A;
		right = GLFW_KEY_D;
		wireOn = GLFW_KEY_UP;
		wireOff = GLFW_KEY_DOWN;
		exit = GLFW_KEY_ESCAPE;
	}
	else
	{
		std::cout << "INPUT_LUA::FILE_FOUND::INPUT_SET" << std::endl;
		LuaRef f = getGlobal(L, "foward");
		LuaRef b = getGlobal(L, "back");
		LuaRef l = getGlobal(L, "left");
		LuaRef r = getGlobal(L, "right");
		LuaRef on = getGlobal(L, "on");
		LuaRef off = getGlobal(L, "off");
		LuaRef ex = getGlobal(L, "exit");

		if (f.isNumber())
		{
			foward = f.cast<int>();
		}

		if (b.isNumber())
		{
			back = b.cast<int>();
		}

		if (l.isNumber())
		{
			left = l.cast<int>();
		}

		if (r.isNumber())
		{
			right = r.cast<int>();
		}

		if (on.isNumber())
		{
			wireOn = on.cast<int>();
		}

		if (off.isNumber())
		{
			wireOff = off.cast<int>();
		}

		if (ex.isNumber())
		{
			exit = ex.cast<int>();
		}
	}
}