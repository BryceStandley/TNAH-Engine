#pragma once
#include <string>
#include "Static.h"
#include "Player.h"
#include "Enemy.h"
#include "Token.h"
#include "Water.h"
#include "BoundingBox.h"
#include "singleton.h"
/**
 * @class GameAssetFactory
 * @brief Holds the information so that game objects can be made in the engine
 * by taking in values that allow us to set the different types
 *
 * @author Christopher Logan
 * @version 01
 * @date 3/04/2021
 *
 *
 * @bugs none to be seen
 *
 **/
class GameAssetFactory
{
public:

		/**
		* @brief Game asset factory contructor with the renderer
		* @param r - The renderer for the game engine
		*/
	GameAssetFactory(Renderer* r) { renderer = r; playerMade = false; id = 1; }

		/**
		* @brief Creates the game object and returns it
		* @param t - The type of object it is, if it does not fit it will return nullptr
		* @param modelName - The model filepath
		* @param shaderV - The vertex shader
		* @param shaderF - the fragment shader
		* @param scale - The object scale
		* @param position -  The inital position
		* @param speed - the speed of movement
		* @return GameObject*
		*/
	GameObject* GetGameObject(std::string t, std::string script, float scale , glm::vec3 position);

private:

		///if the player game object has been made
	bool playerMade;

		///The renderer for the engine
	Renderer* renderer;

		///ids for game objects
	int id;
};

