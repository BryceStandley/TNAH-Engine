
#include <lua/lua.hpp>

#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/Vector.h>

/**
 * @brief a Lua manager that uses the singleton pattern to limit itself to a single instance
 */
class LuaManager
{
public:
	/**
	 * @brief gets and returns the instance of LuaManager
	 * @return static instance of the LuaManager
	 * return 
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
	
	static void runScript(const std::string& path);

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