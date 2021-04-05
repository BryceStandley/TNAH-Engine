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
	void Update(float time);
};

