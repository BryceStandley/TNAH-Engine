#pragma once
#include "GameObject.h"
/**
 * @class Enemy
 * @brief Abstract GameObject class for enemies
 *
 * @author Christopher Logan
 * @version 01
 * @date 25/03/2021
 *
 * @todo Add enemy functionality
 * 
 * @bugs none to be seen
 *
 **/
class Enemy : public GameObject
{
public:
	/*
	* @breif Updates the game object with functionality
	* @param time - the time since the last frame (deltatime)
	*/
	void Update(float time);
};

