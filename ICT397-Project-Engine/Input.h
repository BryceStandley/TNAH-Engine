#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "luaManager.h"
/**
 * @class Input
 * @brief Holds the variables for the keys being pressed on the keyboard
 *
 * @author Christopher Logan
 * @version 01
 * @date 1/04/2021
 *
 *
 * @bugs none to be seen
 *
 **/
using namespace luabridge;
class Input
{
public:
		/**
		* @brief Default constructor that first checks to see if there is a lua file and use it, if not there is a default input scheme
		*/
	Input();

		///The foward input key
	int foward;

		///The backward input key
	int back;
	
		///The left input key
	int left;

		///The right input key
	int right;

		///The wireframeOn input key
	int wireOn;

		///The wireframeOff input key
	int wireOff;

		///The exiting input key
	int exit;
};

