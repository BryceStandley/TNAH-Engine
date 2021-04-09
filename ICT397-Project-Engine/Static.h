#pragma once
#include "GameObject.h"
/**
 * @class Static
 * @brief Abstract GameObject class for static game objects
 *
 * @author Christopher Logan
 * @version 01
 * @date 25/03/2021
 *
 *
 * @bugs none to be seen
 *
 **/
class Static : public GameObject
{
public:
		/**
		* @brief Update function that updates the functionality
		* @param time - the time since the last frame
		*/
	void Update(float time);
};

