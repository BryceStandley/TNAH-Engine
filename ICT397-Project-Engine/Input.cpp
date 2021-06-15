#include "Input.h"

Input::Input()
{
	lua_State* L = LuaManager::getInstance().getLuaState();

	if (luaL_dofile(L, "./res/scripts/input.lua"))
	{
		std::cout << "ERROR::INPUT_LUA::FILE_WAS_NOT_FOUND::DEFAULT_INPUT" << std::endl;
		forward = GLFW_KEY_W;
		back = GLFW_KEY_S;
		left = GLFW_KEY_A;
		right = GLFW_KEY_D;
        toggle = GLFW_KEY_K;
		exit = GLFW_KEY_X;
        debug = GLFW_KEY_P;
        pause = GLFW_KEY_ESCAPE;
	}
	else
	{
		std::cout << "INPUT_LUA::FILE_FOUND::INPUT_SET" << std::endl;
		LuaRef f = getGlobal(L, "forward");
		LuaRef b = getGlobal(L, "back");
		LuaRef l = getGlobal(L, "left");
		LuaRef r = getGlobal(L, "right");
        LuaRef t = getGlobal(L, "toggle");
		LuaRef ex = getGlobal(L, "exit");
        LuaRef d = getGlobal(L, "debug");
        LuaRef p = getGlobal(L, "pause");

		if (f.isNumber())
		{
            forward = f.cast<int>();
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

		if (t.isNumber())
		{
			toggle = t.cast<int>();
		}

		if (ex.isNumber())
		{
			exit = ex.cast<int>();
		}
        if (d.isNumber())
        {
            debug = d.cast<int>();
        }

        if (p.isNumber())
        {
            pause = p.cast<int>();
        }
	}
}