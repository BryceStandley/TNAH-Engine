#include "luaManager.h"

LuaManager::LuaManager() 
{
	luaState = luaL_newstate();
	luaL_openlibs(luaState);
}

lua_State* LuaManager::getLuaState() 
{
	if (luaState == nullptr)
		luaState = luaL_newstate();
	return luaState;
}

void LuaManager::runScript(const std::string &path) 
{
	luaL_dofile(LuaManager::getInstance().getLuaState(), path.c_str());
}
