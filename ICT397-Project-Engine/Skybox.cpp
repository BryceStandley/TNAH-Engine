#include "Skybox.h"
Skybox::Skybox()
{
	using namespace luabridge;
	lua_State* L = LuaManager::getInstance().getLuaState();


	if (luaL_dofile(L, "./res/scripts/skybox.lua"))
	{
		std::cout << "ERROR::SKYBOX_LUA::FILE_NOT_FOUND" << std::endl;
	}
	else
	{
		std::cout << "SKYBOX_LUA::FILE_LOADED" << std::endl;
		std::string right;
		std::string left;
		std::string top;
		std::string bottom; 
		std::string front;
		std::string back;
		std::string vertShader;
		std::string fragShader;

		LuaRef r = getGlobal(L, "right");
		LuaRef l = getGlobal(L, "left");
		LuaRef t = getGlobal(L, "top");
		LuaRef bot = getGlobal(L, "bottom");
		LuaRef f = getGlobal(L, "front");
		LuaRef bac = getGlobal(L, "back");
		LuaRef vs = getGlobal(L, "vs");
		LuaRef fs = getGlobal(L, "fs");

		if (r.isString())
		{
			right = r.cast<std::string>();
		}

		if (l.isString())
		{
			left = l.cast<std::string>();
		}

		if (t.isString())
		{
			top = t.cast<std::string>();
		}

		if (bot.isString())
		{
			bottom = bot.cast<std::string>();
		}

		if (f.isString())
		{
			front = f.cast<std::string>();
		}

		if (bac.isString())
		{
			back = bac.cast<std::string>();
		}

		if (vs.isString())
		{
			vertShader = vs.cast<std::string>();
		}

		if (fs.isString())
		{
			fragShader = fs.cast<std::string>();
		}

		cubeFaces.emplace_back(right);
		cubeFaces.emplace_back(left);
		cubeFaces.emplace_back(top);
		cubeFaces.emplace_back(bottom);
		cubeFaces.emplace_back(front);
		cubeFaces.emplace_back(back);
		Shader s(vertShader.c_str(), fragShader.c_str());
		skyShader = s;
	}

	SetSkyVerts();
}
Skybox::Skybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back, std::string vertexShader, std::string fragmentShader)
{
	cubeFaces.emplace_back(right);
	cubeFaces.emplace_back(left);
	cubeFaces.emplace_back(top);
	cubeFaces.emplace_back(bottom);
	cubeFaces.emplace_back(front);
	cubeFaces.emplace_back(back);
	Shader s(vertexShader.c_str(), fragmentShader.c_str());
	skyShader = s;
	SetSkyVerts();
	std::cout << "Other: " << skyVerts.size() << std::endl;
}

void Skybox::SetSkyVerts()
{
	float skyBoxVertices[108] = {
		// positions
		-1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f,
		1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f,

		-1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f,
		-1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,

		1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,

		-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f,
		1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f };

	std::vector<float> temp(std::begin(skyBoxVertices), std::end(skyBoxVertices));
	skyVerts = temp;
}