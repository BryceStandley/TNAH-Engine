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

		///The forward input key
	int forward;

		///The backward input key
	int back;
	
		///The left input key
	int left;

		///The right input key
	int right;

	//Wireframe toggle
    int toggle;

		///The exiting input key
	int exit;

    //The key to toggle the debug panel
    int debug;

    ///Key to toggle the pause menu
    int pause;
};

