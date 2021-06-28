#pragma once
#include <lua/lua.hpp>

#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/Vector.h>

	/**
	* @class luaManager
	* @brief A class that uses the singleton design pattern to provide one instance of the lua_State, which can be used to assist in lua scripting  
	*
	* @author Dylan Blereau
	* @version 01
	* @date 30/03/2021 Dylan Blereau, Started
	*
	*
	**/ 
class LuaManager
{
public:
		/**
		* @brief gets and returns the instance of LuaManager
		* @return static instance of the LuaManager
		*/
	static LuaManager& getInstance()
	{
		static LuaManager instance;
		return instance;
	}

		/**
		* @brief Returns the lua state
		* @return The Lua state
		*/
	lua_State* getLuaState();


	/// Singletons shouldn't be cloneable
	LuaManager(const LuaManager& other) = delete;	 
	
	/// Singletons shouldn't be assignable
	void operator=(const LuaManager&) = delete;

private:
		/**
		* @brief Returns the lua state
		* @return The Lua state
		*/
	lua_State* luaState = nullptr;

	/**
	 * @brief default constructor
	 * 
	 */
	LuaManager();

	/**
	 * @brief destructor
	 * 
	 */
	~LuaManager() {};

};