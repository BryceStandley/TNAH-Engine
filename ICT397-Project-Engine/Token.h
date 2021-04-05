#pragma once
#include "GameObject.h"
/**
 * @class Token
 * @brief Abstract GameObject class for in game tokens
 *
 * @author Christopher Logan
 * @version 01
 * @date 25/03/2021
 *
 * @todo add functionality for the tokens
 *
 * @bugs none to be seen
 *
 **/
class Token : public GameObject
{
public:
		/*
		* @breif Updates the game object with functionality
		* @param time - the time since the last frame (deltatime)
		*/
	void Update(float time);
};

